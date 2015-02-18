
#include <Servo.h>
#include <Oscillator.h>

//-- Declare two oscillators
Oscillator osc[4];

//-- Global parameters for the oscillators
//-- Change this parameters for generating different gaits

//-- Gait 1: Moving forward
const int A[4]= {15, 15, 30, 30};
const int O[4] = {-18, 7, -6, -11};
const int T =1000;
const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

//-- Gait: Moving forward slow
//const int A[4]= {15, 15, 30, 30};
//const int O[4] = {-18, 7, -6, -11};
//const int T =3000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Moving forward faster - small steps
//const int A[4]= {10, 10, 10, 10};
//const int O[4] = {-18, 7, -6, -11};
//const int T =500;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Moving backwards very slow
//const int A[4]= {15, 15, 30, 30};
//const int O[4] = {-18, 7, -6, -11};
//const int T =3000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 

//-- Gait:Turning left
//const int A[4]= {15, 15, 10, 30};
//const int O[4] = {-18, 7, -6, -11};
//const int T =3000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait Turning right
//const int A[4]= {15, 15, 30, 10};
//const int O[4] = {-18, 7, -6, -11};
//const int T =3000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Right side moon walker :-)
//const int A[4]= {25, 25, 0, 0};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: left side moon walker :-)
//const int A[4]= {25, 25, 0, 0};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Superposition: moonwalker + fordward
//const int A[4]= {25, 25, 30, 30};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Swing
//const int A[4]= {25, 25, 0, 0};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

//-- Gait: up-down
//const int A[4]= {25, 25, 0, 0};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)};

//-- Gait: flapping
//const int A[4]= {15, 15, 8, 8};
//const int O[4] = {-18 - A[0] + 10, 7 + A[1] - 10, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};

//-- Test
//const int A[4]= {15, 15, 8, 8};
//const int O[4] = {-18 - A[0] + 10, 7 + A[1] - 10, -6, -11};
//const int T =500;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};


void setup()
{
  //-- Attach the oscillators to the two servos
  //-- SERVO 2 and SERVO 4 for the skymega
  //-- If using arduino, you can use the pin numbers (8 and 9 for example)
  osc[0].attach(9);
  osc[1].attach(8);
  osc[2].attach(7);
  osc[3].attach(6);

  //-- Set the oscillators parameters: amplitude, period, offset and phase
  for (int i=0; i<4; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(T);
    osc[i].SetPh(phase_diff[i]);

  }
}

void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<4; i++)
    osc[i].refresh();
}


