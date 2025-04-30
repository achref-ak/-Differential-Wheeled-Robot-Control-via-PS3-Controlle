#include <Ps3Controller.h>
#define acc 250
#define accDelay 250
#define maxspeed 100 // max value frome the center (between 0 and 126)
#define deadband 5
#define Max 230
#define speedPin 26
#define steerPin 25
int speed ;
int steer ;
int previousTime2;
int cmdSpeed=126;
int cmdSteer=126;


void init_Output()
{
 pinMode(speedPin,OUTPUT);
 pinMode(steerPin,OUTPUT);
}
void adjust_Value()
{
   speed=map(Ps3.data.analog.stick.ry,-127,127,126+maxspeed,126-maxspeed);
   steer=map(Ps3.data.analog.stick.lx,-127,127,126-maxspeed,126+maxspeed);
   
   if (speed<(126+deadband) && speed>(126-deadband)) speed=126;
   if (steer<(126+deadband) && steer>(126-deadband)) steer=126;
   speed=constrain(speed,0,Max);
   steer=constrain(steer,0,Max);
}

void stop()
{
 dacWrite(speedPin, 126);
 dacWrite(steerPin, 126);
}
void setup()
{
    Serial.begin(115200);
    init_Output();
    Ps3.begin("58:56:00:00:f4:92");
    Serial.println("Ready.");
    stop();
    previousTime2=millis();
}

void loop()
{
    if(Ps3.isConnected())
    {
      adjust_Value();
     
       //Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       //Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.print("speed   ");
       Serial.print(cmdSpeed);
       Serial.print(";  steer ");
       Serial.println(cmdSteer);
       if( (millis() - previousTime2) > accDelay)
  {
   previousTime2 = millis();
   if( cmdSpeed > speed )
   {
    cmdSpeed -= acc;
    cmdSpeed = max(speed, cmdSpeed) ;
   }
   if( cmdSpeed < speed )
   {
    cmdSpeed += acc;
    cmdSpeed = min(speed, cmdSpeed) ;
   }   
   if( cmdSteer > steer )
   {
    cmdSteer -= acc;
    cmdSteer = max(steer, cmdSteer) ;
   }
   if( cmdSteer < steer )
   {
    cmdSteer += acc;
    cmdSteer = min(steer, cmdSteer) ;
   }      
  }
       dacWrite(speedPin, cmdSpeed);
       dacWrite(steerPin, cmdSteer);
    } else
    {
    stop();
    }



}