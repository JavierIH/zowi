/*  
 *  ShotDetector.cpp
 *
 *  Author/s:
 *    Miguel Hernando
 *
 *  Revision history:
 *    04-2015: Stable version (Miguel Hernando)
 *
 *  Licenses:
 *    GPL license
 */

#include "Arduino.h"

/*******************************************************************************
 *                              Macro Definitions                              *
 ******************************************************************************/

#define NUM_TOTAL 100
#define NUM_SHOT 10
#define MARGIN 200

/*******************************************************************************
 *                             Function Definitions                            *
 ******************************************************************************/

bool detectShot()
{
  // Static variables
  static int counter = 0;
  static int measure[NUM_TOTAL];

  int ambientLight;     // Average for each cycle
  int shotLight;        // Calculation of the NUM_SHOT last measures
  int lightIntensity;   // Measure for each cycle

  // Moving average of NUM_TOTAL - NUM_SHOT elements
  long int accum = 0;

  // Every cycle analog pin is read
  lightIntensity = analogRead(0);
  measure[(counter++) % NUM_TOTAL] = lightIntensity;
  
  // At the beginning or after an impact, it stores NUM_TOTAL cycles before
  // starting to detect a shot
  if(counter < NUM_TOTAL)
    return false;

  // Calculate the average of the light intensity of the last NUM_TOTAL
  // measures, removing possible shots
  for(int i = 0; i < (NUM_TOTAL-NUM_SHOT); i++)
    accum += measure[(counter + i) % NUM_TOTAL];
  
  ambientLight = (int)(accum / (NUM_TOTAL - NUM_SHOT));

  // Calculate the light intensity of the last NUM_SHOT measures
  accum = 0;

  for(int i = 0; i < NUM_SHOT; i++)
    accum += measure[(counter + NUM_TOTAL - i) % NUM_TOTAL];

  shotLight = (int)(accum / (NUM_SHOT));

  // There is an impact if the difference between "shotLight" and 
  // "ambientLight" is greater than MARGIN
  if(shotLight - ambientLight > MARGIN)
  {
    // Impact
    counter = 0;
    return true;
  }
  
  return false;
}
