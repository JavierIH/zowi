//----------------------------------------------------------------
//-- Zowi: Testing its locomotion gaits
//-- (c) BQ. Released under a GPL licencse
//-- July 2015
//-- Authors:  Javier Isabel:  javier.isabel@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//-----------------------------------------------------------------
//-- Try and combine the different locomotion gaits!
//-----------------------------------------------------------------


//----------------------------------------------------------------------
//--- These .h files are included in Zowi.h, but for unkown reasons
//--  (IT SHOULD BE FIXED) if not declared first here, there appear 
//-- a compilation error
//----------------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

//-- Zowi Library
#include <Zowi.h>

//-- First step: Configure the pins where the servos are attached
/*

         --------------- 
        |               |
        |     O   O     |
        |               |
 YR ==> |               | <== YL
         --------------- 
            ||     ||
            ||     ||
            ||     ||
 RR ==>   -----   ------  <== RL
          -----   ------

*/

#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2

//-- Second step:  Determine the Servo Trim values
#define TRIM_RR   -7
#define TRIM_RL   -2
#define TRIM_YR   0
#define TRIM_YL  -14

//-- This is Zowi!!
Zowi z;


void setup()
{
  //---------- Zowi Initialization
  
    //--  Set the servo pins
    z.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR);
    
    //-- Set the servo trims
    z.setTrims(TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR);
}

void loop()
{
  //-- Zowi at rest position
  z.home();
  delay(500);
  
  //-- Make zowi walk forward and backward!
  //-- Parameters: Number of steps,  Period in ms, direction: FORWARD
    
  z.walk(4, 2000, FORWARD);  //-- Move forward. Slow
  z.walk(4, 1000, FORWARD);  //-- Move forward. Faster
  
  z.home();
  delay(500);
  
  //-- Make zowi walk backward
  z.walk(4, 1000, BACKWARD);  //-- Move backward. Fast
  z.walk(4, 2000, BACKWARD); //-- Move backward slot
    
  //-- Make zowi turn left and right
  //z.turn(3, 2000, RIGHT);
  //z.turn(3, 2000, LEFT);
  
  //-- Make zowi move up and down
  //z.updown(6, 500, SMALL);
  //z.updown(6, 500, MEDIUM);
  //z.updown(6, 500, BIG);
  //z.updown(2, 4000, BIG);
  
  //-- Zowi performing the moonwalker!!
  //z.moonwalker(3, 2000, 30, LEFT);
  //z.moonwalker(3, 2000, 30, RIGHT);
  
  //-- Zowi moving side to side
  //z.swing(6, 600, 10);
  //z.swing(4, 2000, 40);
  
  
  //-- Zowi doing the "crusaito": A mixture between walk and moonwalker
  //z.crusaito(6, 2000, 40, LEFT);
  //z.crusaito(6, 2000, 40, RIGHT);
  
  //-- Zowi moving backward and forward in a different way
  //z.flapping(10, 600, 10, FORWARD);
  //z.flapping(10, 600, 10, BACKWARD);
  
  z.home();
  
  
  //-- Do not move anymore
  while(1);
}



