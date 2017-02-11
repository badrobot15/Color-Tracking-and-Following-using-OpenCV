
byte m1p1 = 2;
byte m1p2 = 3;
byte m2p1 = 4;
byte m2p2 = 7;
byte pwm1 = 5;
byte pwm2 = 6;
byte pwmVal = 160;

int PD = 0;
int P = 0;
int D = 0;
int length = 0;
int radius = 0;
int pre_len = 0;

float Kp = 0.25;
float Kd = 0.15;

char inChar;
String inputStringL="",inputStringR="";

void setup() {
  pinMode(m1p1,OUTPUT);
  pinMode(m1p2,OUTPUT);
  pinMode(m2p1,OUTPUT);
  pinMode(m2p2,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  Serial.begin(9600);
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
      }break;
    }
    inputStringL += inChar;  
  }
  length = inputStringL.toInt();
  radius = inputStringR.toInt();
  if((length < 10 && length >= 0) || (length > -10 && length <= 0)){
    length = 0;
  }else if((length > 320) || (length < -320)){
    length = 0;    
  }else{
    P = (length * Kp);
    D = Kd * (length - pre_len);
    PD = P + D;
  }
  if(PD >= 1){
    rotate_left(PD);
  }else if(PD <= -1){
    rotate_right(-PD);
  }
  if(radius > 60){
   fwd(); 
  }else if(radius < 30 && radius > 5){
   back(); 
  }
  delay(50);
  pre_len = length;
  inputStringL = "";
  inputStringR = "";
  PD = 0;
  radius = 0;
  analogWrite(pwm1,0);
  analogWrite(pwm2,0);  
}

void rotate_right(int pd_val){
  digitalWrite(m1p1,LOW);
  digitalWrite(m1p2,HIGH);
  analogWrite(pwm1,pwmVal);
  digitalWrite(m2p1,LOW);
  digitalWrite(m2p2,HIGH);
  analogWrite(pwm2,pwmVal);
  delay(pd_val);
}

void rotate_left(int pd_val){
  digitalWrite(m1p1,HIGH);
  digitalWrite(m1p2,LOW);
  analogWrite(pwm1,pwmVal);
  digitalWrite(m2p1,HIGH);
  digitalWrite(m2p2,LOW);
  analogWrite(pwm2,pwmVal);
  delay(pd_val);  
}

void fwd(){
  digitalWrite(m1p1,LOW);
  digitalWrite(m1p2,HIGH);
  analogWrite(pwm1,pwmVal);
  digitalWrite(m2p1,HIGH);
  digitalWrite(m2p2,LOW);
  analogWrite(pwm2,pwmVal);
  delay(100);
}

void back(){
  digitalWrite(m1p1,HIGH);
  digitalWrite(m1p2,LOW);
  analogWrite(pwm1,pwmVal);
  digitalWrite(m2p1,LOW);
  digitalWrite(m2p2,HIGH);
  analogWrite(pwm2,pwmVal);
  delay(100);
}
