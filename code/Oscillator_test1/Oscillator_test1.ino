//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//--
//-- Example 5: A mini-wave is used for the locomotion of
//-- a two modules worm robot
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), April-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
//#include "skymega.h"

//-- Declare two oscillators
Oscillator osc[4];

//-- Global parameters for the oscillators
//-- Change this parameters for generating different mini-waves
const int A[4]= {15, 15, 30, 30};
const int O[4] = {-18, 7, -6, -11};
const int T=1000;
const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 

void setup()
{
  //-- Attach the oscillators to the two servos
  //-- SERVO 2 and SERVO 4 for the skymega
  //-- If using arduino, you can use the pin numbers (8 and 9 for example)
  osc[0].attach(9);
  osc[1].attach(8);
  osc[2].attach(7);
  osc[3].attach(6);

  //-- Configure the oscillators with the same parameters
  for (int i=0; i<4; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(T);

  }

  //-- Set the phase difference
  for (int i=0; i<4; i++) 
    osc[i].SetPh(phase_diff[i]);

}

void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<4; i++)
    osc[i].refresh();
}


