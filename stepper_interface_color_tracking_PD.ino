#include <Stepper.h>

#define motorSteps 200

Stepper myStepper(motorSteps, 8,9,10,11); 
int pd = 0,P = 0,D = 0,length = 0,radius = 0,pre_len = 0;
float Kp = 0.25,Kd = 0.15;
char inChar;
String inputStringL="",inputStringR="";

void setup() {
  myStepper.setSpeed(60);
  Serial.begin(115200);
}

void loop() {
  while(Serial.available())
  {
    inChar = Serial.read();
    if(inChar == '#'){
      while(Serial.available()){
        inChar = Serial.read();
        if(inChar == '/'){
          break;
        }
        inputStringR += inChar;
      }
    }
    inputStringL += inChar;  
  }
  length = inputStringL.toInt();
  radius = inputStringR.toInt();
  if((length < 35 && length > 0) || (length > -35 && length < 0)){
    length = 0;
  }else if((length > 320) || (length < -320)){
    length = 0;    
  }
  P = (length * Kp);
  D = Kd * (length - pre_len);
  
  pd = P + D;
  
  myStepper.step(pd);
  
  delay(50);
  pre_len = length;
  inputStringL = "";
  inputStringR = "";
}
