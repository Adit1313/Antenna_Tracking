#include <Servo.h> 
 
Servo pan;  // pan servo
Servo tilt; // tilt servo

int led = 13;
long lastTilt = 90L;
long lastPan = 90L;
int dir = 1;
int pos = 0;
int tiltDelay = 0;
long minPWM = 1000L;
long maxPWM = 2000L;
long panVal = 0L; 
long tiltVal = 0L;
long interpVal = 0L;

String cmd = "";
String panStr = "";
String tiltStr = "";

void setup() 
{ 
  pan.attach(9);  
  tilt.attach(10);
  
  Serial.begin(57600);

  pinMode(led, OUTPUT);     

  // Origin for both servos
  tilt.write(lastTilt);
  pan.write(lastPan);
} 
 
 
void loop() 
{ 
  if (Serial.available()) 
  {
    char ch = Serial.read();  
    
    if (ch == 10)
    {
      digitalWrite(led, HIGH);
      
      // Line feed is the command char
      if (cmd.startsWith("!!!PAN:"))
      {
        panStr = cmd.substring(7,11);
      
        if (cmd.substring(12,16) == "TLT:")
        
        {
          tiltStr = cmd.substring(16,20);
        }

        if (panStr != "")
        {
           panVal = panStr.toInt();
           if (panVal < minPWM)
           {
             panVal = minPWM;
           }        
         
           if (panVal > maxPWM)
           {
             panVal = maxPWM;
           }
       
           interpVal = map(panVal, minPWM, maxPWM, 0, 180); 
         
            if (interpVal > 180)
            {
              interpVal = 180;
            }
        
            if (interpVal < 0)
            {
              interpVal = 0;
            }

            pan.write(interpVal);
            lastPan = interpVal;
        }
      
        if (tiltStr != "")
        {
           tiltVal = tiltStr.toInt();
           if (tiltVal < minPWM)
           {
             tiltVal = minPWM;
           }        
         
           if (tiltVal > maxPWM)
           {
             tiltVal = maxPWM;
           }
         
           interpVal = map(tiltVal, minPWM, maxPWM, 0, 180);
           
            if (interpVal > 180)
            {
              interpVal = 180;
            }
          
            if (interpVal < 0)
            {
              interpVal = 0;
            }

            dir = 1;
            if (interpVal < lastTilt)
            {
              dir = -1;
            }
          
            if (tiltDelay > 0)
            {
              // Slow down tilt by stepping to it's destination
              for (pos = lastTilt; pos != interpVal; pos += dir)
              {                                  
                tilt.write(pos);              
                delay(tiltDelay);                       
              } 
            }
            else
            {
              tilt.write(interpVal);
            }
            tilt.write(interpVal);
            lastTilt = interpVal;
        }
      }
      else if (cmd.startsWith("!!!TLTDLY:"))
      {
        cmd = cmd.substring(10,14);
        tiltDelay = cmd.toInt();
      }
      
      panStr = "";
      tiltStr == "";
      cmd = "";

      digitalWrite(led, LOW);
    }
    else
    {
      cmd += ch;
    }
  }
} 
