#include <Servo.h> 

#define MAX_CH 2

#define TRIM_RR -14
#define TRIM_RL -9
#define TRIM_YR -11
#define TRIM_YL -9

#define PIN_RR 4
#define PIN_RL 5 //8
#define PIN_YR 2
#define PIN_YL 3

int channel[MAX_CH];

Servo sRR; //roll right
Servo sRL; //roll left
Servo sYR; //yaw right                       
Servo sYL; //yaw left


void setup() {
  Serial.begin(19200);
  sRR.attach(PIN_RR);
  sRL.attach(PIN_RL);
  sYR.attach(PIN_YR);
  sYL.attach(PIN_YL);
  channel[0]=90;
  channel[1]=90;  
  
  sRR.write(90+TRIM_RR);
  sRL.write(90+TRIM_RL);
  sYR.write(90+TRIM_YR);
  sYL.write(90+TRIM_YL);
}

void loop() {
  if(Serial.available()>MAX_CH*2-1){
    while(Serial.read()!=0);
    for (int i=0;i<MAX_CH;i++) channel[i]=((int)Serial.read());
    
    sRR.write(channel[1]+45+TRIM_RR);  
    sRL.write(channel[1]+45+TRIM_RL); 
    sYR.write(channel[0]+45+TRIM_YR);  
    sYL.write(channel[0]+45+TRIM_YL);    
  }
}

