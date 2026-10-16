/*  
 *  Scopum Project
 *
 *  Author/s:
 *    Original code by Juan González Gómez (Obijuan)
 *    Adaptation for the Scopum Project by Hacklab Madrid
 *
 *  Revision history:
 *    02-2015: Stable version of Oscillator Server Version 2
 *      (Juan González Gómez)
 *    04-2015: Adaptation for the Scopum Project (Hacklab Madrid)
 *
 *  Licenses:
 *    GPL license
 *
 *  Notes:
 *    Serial commands for accesing the servos
 *    The sintax is <servo_id><cmd_id>[<value>]<CMD_END> were:
 *      <servo_id>  Servo identificacion:  ASCII characters: a, b, c, d ....
 *      <cmd_id>    Type of frame (stop, play, SetA, SetO...)
 *      <angle>     Angle in degrees (in ASCII). The range is [-90, 90]
 *                  In some commands this field is not used
 *      <CMD_END>   End of Frame  (ASCII character CR)
 *
 *  Examples:
 *    aP\r   -> Play the oscillator on sevo a
 *    bS\r   -> Stop the oscillator on servo b
 *    aA40\r -> Set the amplitude of Oscillator of servo a to 40 degrees
 */

#include <Servo.h>
#include "Oscillator.h"

/*******************************************************************************
 *                              Macro Definitions                              *
 ******************************************************************************/

// Scopum state
#define DEAD 0
#define ALIVE 1

// Dies for 2 seconds
#define MILISECS_DEAD    2000

/*******************************************************************************
 *                               Local Variables                               *
 ******************************************************************************/

// Constants
const int led = 13;          // Led for debugging
const int NOSC = 4;          // Number of servos controlled by the server
const int NCSERVOS = 2;      // Number of servos that are not controlled by the
                             // server, but manually controlled
const int canionPin = 12;    // Emitting diode on the weapon
const int pointerPin = 11;   // Laser pin
const int buzzerPin = 13;    // Buzzer pin
const int soundConst = 8;

// Constant for the frames
const char CMD_END = '\r';   // Character end of frame
                             // CR is chosen for working with gtkterm correctly
                             // in Linux
                             // If the arduino terminal is used, Select the
                             // option "carriage return"

// Sound
boolean piumEnable = false;
boolean deathEnable = false;

// Command id's                            
const unsigned char CMD_STOP = 'S';   // Stop the oscillaltor
const unsigned char CMD_PLAY = 'P';   // Play the oscillator
const unsigned char CMD_SET_A = 'A';  // Set Amplitude
const unsigned char CMD_SET_O = 'O';  // Set Offset
const unsigned char CMD_SET_P = 'H';  // Set phase
const unsigned char CMD_SET_T = 'T';  // Set Period
const unsigned char CMD_NONE = 0;

const unsigned char CMD_UP = 'U';     // Upward movement of the arm
const unsigned char CMD_DOWN = 'D';   // Downward movement of the arm
const unsigned char CMD_SHOT = 'I';   // Shot weapon
const unsigned char CMD_PNT_ON = '1'; // Laser ON 
const unsigned char CMD_PNT_OFF = '0';// Laser OFF

// Array of oscillators
Oscillator osc[NOSC];

// Array of controled servos, not oscillators
Servo cser[NCSERVOS];   // The first position correspond with the weapon, the
                        // second with the arm
int angle[NCSERVOS];

// Variables
unsigned char SCOPUM_STATE = ALIVE;
long deathMillis;
long SHOT_TIME;
int shotTime;
long shotMillis;

// Command receiver state
const int WAITING_SERVO_ID = 1;
const int WAITING_CMD_ID = 2;
const int WAITING_VALUE = 3;
const int WAITING_END = 4;

int state = WAITING_SERVO_ID;   // Initial state

String inputString = "";        // A string to hold incoming data

int si;                         // Servo index
int cmd = CMD_NONE;             // Command type
int value;                      // Value
bool cmd_ok = false;

/*******************************************************************************
 *                             Function Declarations                           *
 ******************************************************************************/
 
// Scopum functions
bool detectShot();
void armUp(int id, int value);
void armDown(int id, int value);
void pointer(char state);
void shot();

/*******************************************************************************
 *                                     SETUP                                   *
 ******************************************************************************/
void setup()
{
  // Buzzer
  pinMode(buzzerPin, OUTPUT);
  
  // Configure the led 
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // Attach the oscillators to the servos
  osc[0].attach(9);    // Foot right (looking at the front of the robot)
  osc[1].attach(8);    // Foot left
  osc[2].attach(7);    // Leg right
  osc[3].attach(6);    // Leg left
  cser[0].attach(5);   // Arm right
  cser[1].attach(4);   // Arm left
  cser[2].attach(10);  // Head

  // Initially the oscillators are stopped
  for(int i = 0; i < NOSC; i++)
  {
    osc[i].Stop();
    //osc[i].SetA(10); // debugging!
  }  
  
  for(int i = 0; i < NCSERVOS; i++)
  {
    cser[i].write(90);
    angle[i]=90;
  }

  // Setup usb serial connection to computer
  Serial.begin(19200);
  delay(500);
  
  // Debug
  Serial.println("Server ready");
  
  // Scopum state
  SCOPUM_STATE = ALIVE;

}

/*******************************************************************************
 *                                     LOOP                                    *
 ******************************************************************************/
void loop()
{
  // Check possible shot
  if(digitalRead(canionPin) == HIGH)
  {
    shotTime = millis() - shotMillis;
    
    if(shotTime > SHOT_TIME)
      digitalWrite(canionPin, LOW);
  }
  
  // Check possible impact 
  if((detectShot()) && (SCOPUM_STATE == ALIVE))
  {
    SCOPUM_STATE = DEAD;
    deathEnable = true;

    deathMillis = millis();
  }
  
  // Get and execute the commands
  getCommands();
  
  // When Scopum dies, moves his arms and head and screams
  if(SCOPUM_STATE == DEAD) 
  {
    int tiempo=millis() - deathMillis;
    
    if(tiempo > MILISECS_DEAD)
      SCOPUM_STATE=ALIVE; 
    
    if((tiempo / 170) % 2)
    {
      cser[0].write(5 + tiempo % 170);
      cser[1].write(175 - tiempo % 170);
      cser[2].write(175 - tiempo % 170);
    }
    else
    {
      cser[1].write(5 + tiempo % 170);
      cser[0].write(175 - tiempo % 170);
      cser[2].write(175 - tiempo % 170);
    }
  }

  sound();
}

/*******************************************************************************
 *                             Function Definitions                            *
 ******************************************************************************/

void getCommands()
{
  // Read the incoming commands
  while (Serial.available())
  {
    // Read the received char
    char inChar = (char)Serial.read();
      
    // Depending on the state
    switch(state)
    {    
      // Read the servo ID, we also use it for the weapon 
      case WAITING_SERVO_ID:
        
        inputString = "";
        
        // Calculate the index
        si = inChar - 'a';
        
        if (inChar=='w'){
          state = WAITING_CMD_ID;
          break;
        }  

        // Only if the servo index is ok, the command is accepted
        if (si >= 0 && si < NOSC + NCSERVOS)
        {
          state = WAITING_CMD_ID;
        }
        // Otherwise it is ignored. The state is not changed
        else
        {
          state = WAITING_SERVO_ID;
          Serial.println("Wrong Servo id");
        }
        break;
          
      // Read the cmd ID
      case WAITING_CMD_ID:
      
         cmd = inChar;
           
         // The next state depends on the command id
         switch(cmd)
         {
           case CMD_STOP:
           case CMD_PLAY:
           case CMD_PNT_ON: 
           case CMD_PNT_OFF: 
             state = WAITING_END;
             break;
 
           case CMD_SET_O:
           case CMD_SET_A:
           case CMD_SET_P:
           case CMD_SET_T:
           case CMD_UP:  
           case CMD_DOWN: 
           case CMD_SHOT:
             state = WAITING_VALUE;
             break;
               
           // If the command is unknow, move to the initial state  
           default:
             state = WAITING_SERVO_ID;
             Serial.println("Wrong command");
         }
         break;  
         
       // Read the value field
       case WAITING_VALUE:
           
         // Check if inChar is a valid digit
         if(isdigit(inChar) || inChar=='-' || inChar == CMD_END)
         {
           // Add the char to the String for latter processing
           inputString += inChar;
             
           // When end of frame reached...
           if(inChar == CMD_END)
           {
             value = inputString.toInt();
             state = WAITING_SERVO_ID;
             cmd_ok = true;
             runCommand();
             //Serial.print(inputString);  // For debugging
           }
             
         }
         // Invalid digit
         else {
           // Move to the initial state. Invalid command
           state = WAITING_SERVO_ID;
           cmd_ok = false;
           Serial.println("Wrong value");
         }
         break;
         
       // Read the end of the frame
       case WAITING_END:
         
         // The next state is the initial, in any case
         state = WAITING_SERVO_ID;
         
         // End of frame received correctly
         if (inChar == CMD_END) {
           cmd_ok = true;             // The command is ok!
           runCommand();
         }  
         else {
           cmd_ok = false;   // Invalid frame. It will be ignored
         }
         break;
          
    } // End switch
      
  } // End While
  
  if(SCOPUM_STATE == DEAD)return;
  
  // Refresh the oscillators!
  for (int i = 0; i < NOSC; i++)
  {
    osc[i].refresh();
  }  
}

void runCommand()
{
  // If the frame received is ok... process!
  if (cmd_ok)
  {
    //Serial.println("OK");
    switch(cmd)
    {  
      // Command play
      case CMD_PLAY:
        osc[si].Play();
        break;
        
      // Command stop
      case CMD_STOP:
        osc[si].Stop();
        break;
      
      // Set the amplitude
      case CMD_SET_A:
        osc[si].SetA(abs(value));
        break;
        
      // Set the offset
      case CMD_SET_O:
        osc[si].SetO(value);
        break;
        
      // Set the phase
      case CMD_SET_P:
        osc[si].SetPh(DEG2RAD(value));
        break;
        
      // Set the period
      case CMD_SET_T:
        osc[si].SetT(abs(value));
        break;
        
      case CMD_UP:
        armUp(si, value);//Used for both arms
        break;
        
      case CMD_DOWN:
        armDown(si, value);//Used for both arms
        break;
        
      case CMD_PNT_ON:
        pointer(CMD_PNT_ON);//Pointer on
        break;
        
      case CMD_PNT_OFF:
        pointer(CMD_PNT_OFF);//Pointer off
        break;
        
      case CMD_SHOT:
        shotMillis = millis();
        digitalWrite(canionPin, HIGH);//Shot "value" miliseconds
        SHOT_TIME = value;

        // Pium
        piumEnable = true;
        break;
    }
    
    cmd_ok = false;
  }  
}

void armUp(int id, int value){

  angle[id - NOSC] += value;
  cser[id - NOSC].write(angle[id - NOSC]);

}

void armDown(int id, int value)
{
  angle[id - NOSC] -= value;
  cser[id - NOSC].write(angle[id - NOSC]);
}

void pointer(char state)
{
  if(state == '1')
    digitalWrite(pointerPin, HIGH);
  else if(state == '0')
    digitalWrite(pointerPin, LOW);
}

void sound()
{
  if(piumEnable)
    pium();
    
  if(deathEnable)
    death();
}

void pium()
{
  static int counter = 0;
  counter += soundConst;
  
  tone(buzzerPin, (1300 - counter / 2));
  
  if(counter > 1000)
  {
    noTone(buzzerPin);
    counter = 0;
    piumEnable = false;
  }
}

void death() 
{
  static int counter = 0;
  counter += soundConst;
  if(counter < 3000)
  {
    int myTone = random(0,2000);
    tone(buzzerPin, myTone);
  }
  
  if(counter > 3000 && counter < 5000)
    noTone(buzzerPin);
    
  if(counter > 5000 && counter < 7000)
  {
    tone(buzzerPin, 500);
  }
  
  if(counter > 7000 && counter < 10000)
  {
    tone(buzzerPin, 250);
  }
  
  if(counter > 10000)
  {
    noTone(buzzerPin);
    counter = 0;
    deathEnable = false;
  }
}  
