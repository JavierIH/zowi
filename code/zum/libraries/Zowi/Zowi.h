#ifndef Zowi_h
#define Zowi_h


#include "Arduino.h"
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>



class Zowi
{
  public:
    void init(int YL, int YR, int RL, int RR, bool load_calibration=0);
    void setTrims(int YL, int YR, int RL, int RR);
    void saveTrimsOnEEPROM();
    
    void moveServos(int time, int  servo_target[]);
    void oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle);
    
    void walk(float steps=4, int T=1800);
    void turnLeft(float steps, int T);
    void turnRight(float steps, int T);
    void backward(float steps, int T);
    void jump(float steps=1, int T=1000);

 
  private:
  
    Oscillator servo[4];
    int servo_trim[4];
    int servo_position[4];
    
    unsigned long final_time;
    unsigned long partial_time;
    float increment[4];
};

#endif


