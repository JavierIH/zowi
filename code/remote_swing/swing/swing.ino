#include <Servo.h> 

#define MAX_CH 2

Servo servo[4];
int channel[MAX_CH];

Servo sRR; //roll right
Servo sRL; //roll left
Servo sYR; //yaw right                       
Servo sYL; //yaw left

int offset_RR=-18; //Zero point calibration
int offset_RL=7;
int offset_YR=-6;
int offset_YL=-11;


void setup() {
  Serial.begin(19200);
  sRR.attach(9);
  sRL.attach(8);
  sYR.attach(7);
  sYL.attach(6);
  channel[0]=90;
  channel[1]=90;  
  
  sRR.write(90+offset_RR);
  sRL.write(90+offset_RL);
  sYR.write(90+offset_YR);
  sYL.write(90+offset_YL);
  
}

void loop() {
  if(Serial.available()>MAX_CH*2-1){
    while(Serial.read()!=0);
    for (int i=0;i<MAX_CH;i++) channel[i]=((int)Serial.read());
    
    sRR.write(channel[0]+45+offset_RR);  
    sRL.write(channel[0]+45+offset_RL);    
  }
}

