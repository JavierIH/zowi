//----------------------------------------------------------------
//-- Zowi hello world
//-- (c) BQ. Released under a GPL licencse
//-- July 2015
//-- Authors:  Javier Isabel:  javier.isabel@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//-----------------------------------------------------------------
//-- It just makes zowi walk forward and then stop
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
  //z.home();
  //delay(500);
  
  //-- Make zowi walk forward and backward!
  //-- Parameters: Number of steps,  Period in ms,
    
    
  //-- Make zowi turn left and right
  //z.turn(3, 2000, RIGHT);
  //z.turn(3, 2000, LEFT);
  
  
  //z.updown(6, 500, SMALL);
  //z.updown(6, 500, MEDIUM);
  //z.updown(6, 500, BIG);
  //z.updown(2, 4000, BIG);
  
  //z.moonwalker(3, 2000, 30, LEFT);
  //z.moonwalker(3, 2000, 30, RIGHT);
  
  //z.swing(6, 600, 10);
  //z.swing(4, 2000, 40);
  
  //z.crusaito(6, 2000, 40, LEFT);
  //z.crusaito(6, 2000, 40, RIGHT);
  
  z.flapping(10, 600, 10, FORWARD);
  z.flapping(10, 600, 10, BACKWARD);
  
  z.home();
  
  
  //-- Do not move anymore
  while(1);
}



