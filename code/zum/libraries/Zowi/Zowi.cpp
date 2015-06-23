#include "Zowi.h"
#include <Oscillator.h>

void Zowi::init(int YL, int YR, int RL, int RR, bool load_calibration) {
  servo[0].attach(YL);
  servo[1].attach(YR);
  servo[2].attach(RL);
  servo[3].attach(RR);

  if (load_calibration) {
    for (int i = 0; i < 4; i++) {
      int servo_trim = EEPROM.read(i);
      if (servo_trim > 128) servo_trim -= 256;
      servo[i].SetTrim(servo_trim);
    }
  }
  
  for (int i = 0; i < 4; i++) servo_position[i] = 90;
}

void Zowi::setTrims(int YL, int YR, int RL, int RR) {
  servo[0].SetTrim(YL);
  servo[1].SetTrim(YR);
  servo[2].SetTrim(RL);
  servo[3].SetTrim(RR);
}

void Zowi::saveTrimsOnEEPROM() {
  for (int i = 0; i < 4; i++) EEPROM.write(i, servo[i].getTrim());
}

void Zowi::moveServos(int time, int  servo_target[]) {
  if(time>10){
    for (int i = 0; i < 4; i++)	increment[i] = ((servo_target[i]) - servo_position[i]) / (time / 10.0);
    final_time =  millis() + time;

    for (int iteration = 1; millis() < final_time; iteration++) {
      partial_time = millis() + 10;
      for (int i = 0; i < 4; i++) servo[i].SetPosition(servo_position[i] + (iteration * increment[i]));
      while (millis() < partial_time); //pause
    }
  }
  else{
    for (int i = 0; i < 4; i++) servo[i].SetPosition(servo_target[i]);
  }
  for (int i = 0; i < 4; i++) servo_position[i] = servo_target[i];
}

void Zowi::oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle=1){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T*cycle+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}


void Zowi::walk(float steps, int T){
  int A[4]= {30, 30, 20, 20};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)};

  int cycles=(int)steps;    

  if (cycles >= 1) for(int i=0;i<cycles;i++) oscillateServos(A,O, T, phase_diff);
  oscillateServos(A,O, T, phase_diff,(float)steps-cycles);
}

void Zowi::backward(float steps, int T){
  int A[4]= {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(270), DEG2RAD(270)}; 
    
  int cycles=(int)steps;    

  if (cycles >= 1) for(int i=0;i<cycles;i++) oscillateServos(A,O, T, phase_diff);
  oscillateServos(A,O, T, phase_diff,(float)steps-cycles);
}

void Zowi::turnLeft(float steps, int T){
  int A[4]= {10, 10, 25, 25};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)}; 
    
  int cycles=(int)steps;    

  if (cycles >= 1) for(int i=0;i<cycles;i++) oscillateServos(A,O, T, phase_diff);
  oscillateServos(A,O, T, phase_diff,(float)steps-cycles);
}

void Zowi::turnRight(float steps, int T){
  int A[4]= {20, 20, 30, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
  int cycles=(int)steps;    

  if (cycles >= 1) for(int i=0;i<cycles;i++) oscillateServos(A,O, T, phase_diff);
  oscillateServos(A,O, T, phase_diff,(float)steps-cycles);  
}

void Zowi::jump(float steps, int T){
  int up[]={90,90,150,30};
  moveServos(T,up);
  int down[]={90,90,90,90};
  moveServos(T,down);
}
