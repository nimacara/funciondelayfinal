 #include <QTRSensors.h>
 #include <SoftwareSerial.h>
  int Salida=0;
 const int MIZ= 10;
 const int MDE= 11;
 const int SA=7;  

int AV = 12;//led de arranque
int mode_run=0;
#define NUM_SENSORS             6 
#define NUM_SAMPLES_PER_SENSOR  4  
#define EMITTER_PIN             2 
#define TxD 1
#define RxD 0
#define RPM A8
SoftwareSerial Bluetooth(TxD,RxD);
QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
  
unsigned int sensorValues[NUM_SENSORS];
int mot=0; //este valor lo va a definir el slider

void setup()
{
          pinMode(MIZ,OUTPUT);
          pinMode(MDE,OUTPUT);
          pinMode(AV,OUTPUT);
          pinMode(SA,INPUT);
          pinMode(RPM,INPUT);
        
          analogWrite(MIZ,0);
          analogWrite(MDE,0);
          Bluetooth.begin(9600);
          Serial.begin(9600);
          
          
          
          delay(100);
          
          pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
        for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
        {
          qtra.calibrate();        
          
        }
        digitalWrite(13, LOW);     
        
     /* Serial.begin(9600);
        for (int i = 0; i < NUM_SENSORS; i++)
        {
          Serial.print(qtra.calibratedMinimumOn[i]);
          Serial.print(' ');
        }
        Serial.println();
        
      for (int i = 0; i < NUM_SENSORS; i++)
        {
          Serial.print(qtra.calibratedMaximumOn[i]);
          Serial.print(' ');
        }
          Serial.println();
          Serial.println();
      */
    
       

          
}

void loop()
{
     
     Salida= digitalRead(SA);
    if(Salida==1)
  {
        digitalWrite(AV, HIGH);
        mode_run=1;
        for(int i=0;i<5;i++)
        {
          digitalWrite(AV, HIGH);   // enciende el led
          delay(500);               // espera medio segundo
          digitalWrite(AV, LOW);    // apaga el led
          delay(500);
        }
        
            digitalWrite(AV, HIGH);   // enciende el led
            delay(50);            
            Motores(); 
            int rpm=digitalRead(RPM);
            Bluetooth.println(rpm);
            
            
          
  }
  else 
  {
    digitalWrite(EMITTER_PIN,HIGH);
    delay(75);
    digitalWrite(EMITTER_PIN,LOW);
    delay(75);
    Salida= digitalRead(SA);
  }
}


void Motores()
{


    digitalWrite(AV,HIGH);
        unsigned int position = qtra.readLine(sensorValues);       
         /* for (unsigned char i = 0; i < NUM_SENSORS; i++)
            {
           Serial.print(sensorValues[i]);
            Serial.print('\t');
            }
           Serial.println(); 
             Serial.print(position); 
             Serial.print(" Dere");
             Serial.print (MDE);
             Serial.print(" ");
             Serial.print(" Izq");
             Serial.print(MIZ);
             Serial.print(" ");
             Serial.println('\t');
            */
            //---------------------------------
            
    if((0<=position)&&(position<=249))
            {
              analogWrite(MIZ,120+mot);
              analogWrite(MDE,0+mot);
            } 
    if((250<=position)&&(position<=499))
            {
              analogWrite(MIZ,110+mot);
              analogWrite(MDE,15+mot);
            }    
    if((500<=position)&&(position<=999))
            {
              analogWrite(MIZ,105+mot);
              analogWrite(MDE,40+mot);
            }             
    if((1000<=position)&&(position<=1499))
            {
              analogWrite(MIZ,105+mot);
              analogWrite(MDE,50+mot);
            }       
    if((1500<=position)&&(position<=1999))
            {
              analogWrite(MIZ,105+mot);
              analogWrite(MDE,60+mot);
            }       
    if((2000<=position)&&(position<=2299))
            {
              analogWrite(MIZ,105+mot);
              analogWrite(MDE,70+mot);
            }
//------------------------------------------------------------------------------
    if((2300<=position)&&(position<=2399))
            {
              analogWrite(MIZ,105+mot);
              analogWrite(MDE,90+mot); 
            }
  ///****************************************************///
  /****/    if((2400<=position)&&(position<=2600))///****///
  /****/    {                                     ///****///
  /****/      analogWrite(MIZ,130+mot);             ///****///
  /****/      analogWrite(MDE,130+mot);             ///****/// 
  /****/   }                                      ///****///
  ///****************************************************///
   if((2601<=position)&&(position<=2700))
            {
              analogWrite(MIZ,90+mot);
              analogWrite(MDE,105+mot); 
            }
//--------------------------------------------------------------------------------
            
    if((2701<=position)&&(position<=2999))
            {
              analogWrite(MIZ,70+mot);
              analogWrite(MDE,100+mot);
            }
                
    if((3000<=position)&&(position<=3499))
            {
              analogWrite(MIZ,60+mot);
              analogWrite(MDE,100+mot);
            }
    if((3500<=position)&&(position<=3999))
            {
              analogWrite(MIZ,50+mot);
              analogWrite(MDE,100+mot);
            }
     if((4000<=position)&&(position<=4499))
            {
              analogWrite(MIZ,40+mot);
              analogWrite(MDE,105+mot);
            }
     if((4500<=position)&&(position<=4749))
            {
              analogWrite(MIZ,15+mot);
              analogWrite(MDE,105+mot);
            }  
      if((4750<=position)&&(position<=5000))
            {
              analogWrite(MIZ,0+mot);
              analogWrite(MDE,120+mot);
            }                
 
            
}
