//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan)
//-- GPL license
//--------------------------------------------------------------


#include <Servo.h> 

Servo sRR; //roll right
Servo sRL; //roll left
Servo sYR; //yaw right                       
Servo sYL; //yaw left

int offset_RR=0; //Zero point calibration
int offset_RL=0;
int offset_YR=0;
int offset_YL=0;

int time=500; //Walking parameters
int amp_roll=25;
int amp_yaw=15;


void setup() {Serial.begin(9600);
  sRR.attach(9);
  sRL.attach(8);
  sYR.attach(7);
  sYL.attach(6);

  
  sRR.write(90+offset_RR);
  sRL.write(90+offset_RL);
  sYR.write(90+offset_YR);
  sYL.write(90+offset_YL);
  
}

void loop() {long t=millis();
 
   sRR.write((90+offset_RR)+amp_roll);  
   sRL.write((90+offset_RL)+amp_roll);
   sYR.write((90+offset_YR)+amp_yaw);  
   sYL.write((90+offset_YL)+amp_yaw);   
   delay(time);  
   
   sRR.write((90+offset_RR)+amp_roll);  
   sRL.write((90+offset_RL)+amp_roll);
   sYR.write((90+offset_YR)-amp_yaw);  
   sYL.write((90+offset_YL)-amp_yaw);   
   delay(time);
   
   sRR.write((90+offset_RR)-amp_roll);  
   sRL.write((90+offset_RL)-amp_roll);
   sYR.write((90+offset_YR)-amp_yaw);  
   sYL.write((90+offset_YL)-amp_yaw);   
   delay(time);  
   
   sRR.write((90+offset_RR)-amp_roll);  
   sRL.write((90+offset_RL)-amp_roll);
   sYR.write((90+offset_YR)+amp_yaw);  
   sYL.write((90+offset_YL)+amp_yaw);   
   delay(time); 
   Serial.println(millis()-t);
}

