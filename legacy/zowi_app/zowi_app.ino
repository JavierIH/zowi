
//----------------------------------------------------------------
//-- Zowi basic firmware v2 (Modded for Zowi community edition)
//-- (c) BQ. Released under a GPL licencse
//-- 25 January 2016
//-- Authors:  Javier Isabel:  javier.isabel@bq.com
//--           Anita de Prado: ana.deprado@bq.com
//--           Jose Alberca:   jose.alberca@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//--           Irene Sanz : irene.sanz@bq.com
//-----------------------------------------------------------------
//-- Experiment with all the features that Zowi have!
//-----------------------------------------------------------------

//-- Library to manage external interruptions

//-- Library to manage serial commands
#include <ZowiSerialCommand.h>
ZowiSerialCommand SCmd;  //The SerialCommand object

//-- Zowi Library
#include <Zowi.h>
Zowi zowi;  //This is Zowi!!
 
//---------------------------------------------------------
//-- Configuration of pins where the servos are attached
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
 RR ==>  ------   ------  <== RL
         ------   ------
*/

  #define PIN_YL 2 //servo[0]
  #define PIN_YR 3 //servo[1]
  #define PIN_RL 4 //servo[2]
  #define PIN_RR 5 //servo[3]
//---------------------------------------------------------

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////

const char programID[]="ZOWI_BASE_v2"; //Each program will have a ID

const char name_fac='$'; //Factory name
const char name_fir='#'; //First name

//-- Movement parameters
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements

//---------------------------------------------------------
//-- Zowi has 5 modes:
//--    * MODE = 0: Zowi is awaiting  
//--    * MODE = 1: Dancing mode!  
//--    * MODE = 2: Obstacle detector mode  
//--    * MODE = 3: Noise detector mode   
//--    * MODE = 4: ZowiPAD or any Teleoperation mode (listening SerialPort). 
//--
volatile int MODE=0; //State of zowi in the principal state machine. 
//--------------------------------------------------------- 

unsigned long previousMillis=0;

int randomDance=0;
int randomSteps=0;

bool obstacleDetected = false;


///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){

  //Serial communication initialization
  Serial.begin(19200);  

  //Set the servo pins
  zowi.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
 
  //Uncomment this to set the servo trims manually and save on EEPROM 
    //zowi.setTrims(TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR);
    //zowi.saveTrimsOnEEPROM(); //Uncomment this only for one upload when you finaly set the trims.

  //Set a random seed
  randomSeed(analogRead(A6));

  //Setup callbacks for SerialCommand commands 
  SCmd.addCommand("S", receiveStop);      //  sendAck & sendFinalAck
  //SCmd.addCommand("L", receiveLED);       //  sendAck & sendFinalAck
  SCmd.addCommand("T", recieveBuzzer);    //  sendAck & sendFinalAck
  SCmd.addCommand("M", receiveMovement);  //  sendAck & sendFinalAck
  SCmd.addCommand("H", receiveGesture);   //  sendAck & sendFinalAck
  SCmd.addCommand("K", receiveSing);      //  sendAck & sendFinalAck
  SCmd.addCommand("C", receiveTrims);     //  sendAck & sendFinalAck
  SCmd.addCommand("G", receiveServo);     //  sendAck & sendFinalAck
  SCmd.addCommand("R", receiveName);      //  sendAck & sendFinalAck
  SCmd.addCommand("E", requestName);
  SCmd.addCommand("D", requestDistance);
  SCmd.addCommand("N", requestNoise);
  //SCmd.addCommand("B", requestBattery);
  SCmd.addCommand("I", requestProgramId);
  SCmd.addDefaultHandler(receiveStop);



  //Zowi wake up!
  zowi.sing(S_connection);
  zowi.home();


  //If Zowi's name is '&' (factory name) means that is the first time this program is executed.
  //This first time, Zowi mustn't do anything. Just born at the factory!
  //5 = EEPROM address that contains first name character
  /*if (EEPROM.read(5)==name_fac){ 

    EEPROM.put(5, name_fir); //From now, the name is '#'
    EEPROM.put(6, '\0'); 

    while(true){    
       delay(1000);
    }
  }*/  


  //Send Zowi name, programID & battery level.
  requestName();

  //Smile for a happy Zowi :)
    zowi.sing(S_happy);
    delay(200);
  


  //If Zowi's name is '#' means that Zowi hasn't been baptized
  //In this case, Zowi does a longer greeting
  //5 = EEPROM address that contains first name character
  if (EEPROM.read(5)==name_fir){ 

  previousMillis = millis();
  }
}



///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {


  if (Serial.available()>0 && MODE!=4){
    MODE=4;
  }
  else{

    switch (MODE) {

      //-- MODE 0 - Zowi is awaiting
      //---------------------------------------------------------
      case 0:
      
        //Every 80 seconds in this mode, Zowi falls asleep 
        if (millis()-previousMillis>=80000){
            ZowiSleeping_withInterrupts(); //ZZzzzzz...
            previousMillis=millis();         
        }

        break;
      

      //-- MODE 4 - ZowiPAD or any Teleoperation mode (listening SerialPort) 
      //---------------------------------------------------------
      case 4:

        SCmd.readSerial();
        
        //If Zowi is moving yet
        if (zowi.getRestState()==false){  
          move(moveId);
        }
      
        break;      


      default:
          MODE=4;
          break;
    }

  } 

}  

//-- Function to receive Stop command.
void receiveStop(){

    sendAck();
    zowi.home();
    sendFinalAck();

}

//-- Function to receive buzzer commands
void recieveBuzzer(){
  
    //sendAck & stop if necessary
    sendAck();
    zowi.home(); 

    bool error = false; 
    int frec;
    int duration; 
    char *arg; 
    
    arg = SCmd.next(); 
    if (arg != NULL) { frec=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}
    
    arg = SCmd.next(); 
    if (arg != NULL) { duration=atoi(arg); } // Converts a char string to an integer  
    else {error=true;}

    if(error==true){

      delay(2000);

    }else{ 

      zowi._tone(frec, duration, 1);   
    }

    sendFinalAck();

}


//-- Function to receive TRims commands
void receiveTrims(){  

    //sendAck & stop if necessary
    sendAck();
    zowi.home(); 

    int trim_YL,trim_YR,trim_RL,trim_RR;

    //Definition of Servo Bluetooth command
    //C trim_YL trim_YR trim_RL trim_RR
    //Examples of receiveTrims Bluetooth commands
    //C 20 0 -8 3
    bool error = false;
    char *arg;
    arg=SCmd.next();
    if (arg != NULL) { trim_YL=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { trim_YR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { trim_RL=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { trim_RR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}
    
    if(error==true){

      delay(2000);

    }else{ //Save it on EEPROM
      zowi.setTrims(trim_YL, trim_YR, trim_RL, trim_RR);
      zowi.saveTrimsOnEEPROM(); //Uncomment this only for one upload when you finaly set the trims.
    } 

    sendFinalAck();

}


//-- Function to receive Servo commands
void receiveServo(){  

    sendAck(); 
    moveId = 30;

    //Definition of Servo Bluetooth command
    //G  servo_YL servo_YR servo_RL servo_RR 
    //Example of receiveServo Bluetooth commands
    //G 90 85 96 78 
    bool error = false;
    char *arg;
    int servo_YL,servo_YR,servo_RL,servo_RR;

    arg=SCmd.next();
    if (arg != NULL) { servo_YL=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_YR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_RL=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_RR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}
    
    if(error==true){

      delay(2000);

    }else{ //Update Servo:

      int servoPos[4]={servo_YL, servo_YR, servo_RL, servo_RR}; 
      zowi._moveServos(200, servoPos);   //Move 200ms
      
    }

    sendFinalAck();

}


//-- Function to receive movement commands
void receiveMovement(){

    sendAck();

    if (zowi.getRestState()==true){
        zowi.setRestState(false);
    }

    //Definition of Movement Bluetooth commands
    //M  MoveID  T   MoveSize  
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {moveId=atoi(arg);}
    else{
      delay(2000);
      moveId=0; //stop
    }
    
    arg = SCmd.next(); 
    if (arg != NULL) {T=atoi(arg);}
    else{
      T=1000;
    }

    arg = SCmd.next(); 
    if (arg != NULL) {moveSize=atoi(arg);}
    else{
      moveSize =15;
    }
}


//-- Function to execute the right movement according the movement command received.
void move(int moveId){

  bool manualMode = false;

  switch (moveId) {
    case 0:
      zowi.home();
      break;
    case 1: //M 1 1000 
      zowi.walk(1,T,1);
      break;
    case 2: //M 2 1000 
      zowi.walk(1,T,-1);
      break;
    case 3: //M 3 1000 
      zowi.turn(1,T,1);
      break;
    case 4: //M 4 1000 
      zowi.turn(1,T,-1);
      break;
    case 5: //M 5 1000 30 
      zowi.updown(1,T,moveSize);
      break;
    case 6: //M 6 1000 30
      zowi.moonwalker(1,T,moveSize,1);
      break;
    case 7: //M 7 1000 30
      zowi.moonwalker(1,T,moveSize,-1);
      break;
    case 8: //M 8 1000 30
      zowi.swing(1,T,moveSize);
      break;
    case 9: //M 9 1000 30 
      zowi.crusaito(1,T,moveSize,1);
      break;
    case 10: //M 10 1000 30 
      zowi.crusaito(1,T,moveSize,-1);
      break;
    case 11: //M 11 1000 
      zowi.jump(1,T);
      break;
    case 12: //M 12 1000 30 
      zowi.flapping(1,T,moveSize,1);
      break;
    case 13: //M 13 1000 30
      zowi.flapping(1,T,moveSize,-1);
      break;
    case 14: //M 14 1000 20
      zowi.tiptoeSwing(1,T,moveSize);
      break;
    case 15: //M 15 500 
      zowi.bend(1,T,1);
      break;
    case 16: //M 16 500 
      zowi.bend(1,T,-1);
      break;
    case 17: //M 17 500 
      zowi.shakeLeg(1,T,1);
      break;
    case 18: //M 18 500 
      zowi.shakeLeg(1,T,-1);
      break;
    case 19: //M 19 500 20
      zowi.jitter(1,T,moveSize);
      break;
    case 20: //M 20 500 15
      zowi.ascendingTurn(1,T,moveSize);
      break;
    default:
        manualMode = true;
      break;
  }

  if(!manualMode){
    sendFinalAck();
  }
       
}


//-- Function to receive gesture commands
void receiveGesture(){

    //sendAck & stop if necessary
    sendAck();
    zowi.home(); 

    //Definition of Gesture Bluetooth commands
    //H  GestureID  
    int gesture = 0;
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {gesture=atoi(arg);}
    else 
    {
      delay(2000);
    }

    switch (gesture) {
      case 1: //H 1 
        zowi.playGesture(ZowiHappy);
        break;
      case 2: //H 2 
        zowi.playGesture(ZowiSuperHappy);
        break;
      case 3: //H 3 
        zowi.playGesture(ZowiSad);
        break;
      case 4: //H 4 
        zowi.playGesture(ZowiSleeping);
        break;
      case 5: //H 5  
        zowi.playGesture(ZowiFart);
        break;
      case 6: //H 6 
        zowi.playGesture(ZowiConfused);
        break;
      case 7: //H 7 
        zowi.playGesture(ZowiLove);
        break;
      case 8: //H 8 
        zowi.playGesture(ZowiAngry);
        break;
      case 9: //H 9  
        zowi.playGesture(ZowiFretful);
        break;
      case 10: //H 10
        zowi.playGesture(ZowiMagic);
        break;  
      case 11: //H 11
        zowi.playGesture(ZowiWave);
        break;   
      case 12: //H 12
        zowi.playGesture(ZowiVictory);
        break; 
      case 13: //H 13
        zowi.playGesture(ZowiFail);
        break;         
      default:
        break;
    }

    sendFinalAck();
}

//-- Function to receive sing commands
void receiveSing(){

    //sendAck & stop if necessary
    sendAck();
    zowi.home(); 

    //Definition of Sing Bluetooth commands
    //K  SingID    
    int sing = 0;
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {sing=atoi(arg);}
    else 
    {
      delay(2000);
    }

    switch (sing) {
      case 1: //K 1 
        zowi.sing(S_connection);
        break;
      case 2: //K 2 
        zowi.sing(S_disconnection);
        break;
      case 3: //K 3 
        zowi.sing(S_surprise);
        break;
      case 4: //K 4 
        zowi.sing(S_OhOoh);
        break;
      case 5: //K 5  
        zowi.sing(S_OhOoh2);
        break;
      case 6: //K 6 
        zowi.sing(S_cuddly);
        break;
      case 7: //K 7 
        zowi.sing(S_sleeping);
        break;
      case 8: //K 8 
        zowi.sing(S_happy);
        break;
      case 9: //K 9  
        zowi.sing(S_superHappy);
        break;
      case 10: //K 10
        zowi.sing(S_happy_short);
        break;  
      case 11: //K 11
        zowi.sing(S_sad);
        break;   
      case 12: //K 12
        zowi.sing(S_confused);
        break; 
      case 13: //K 13
        zowi.sing(S_fart1);
        break;
      case 14: //K 14
        zowi.sing(S_fart2);
        break;
      case 15: //K 15
        zowi.sing(S_fart3);
        break;    
      case 16: //K 16
        zowi.sing(S_mode1);
        break; 
      case 17: //K 17
        zowi.sing(S_mode2);
        break; 
      case 18: //K 18
        zowi.sing(S_mode3);
        break;   
      case 19: //K 19
        zowi.sing(S_buttonPushed);
        break;                      
      default:
        break;
    }

    sendFinalAck();
}


//-- Function to receive Name command
void receiveName(){

    //sendAck & stop if necessary
    sendAck();
    zowi.home(); 

    char newZowiName[11] = "";  //Variable to store data read from Serial.
    int eeAddress = 5;          //Location we want the data to be in EEPROM.
    char *arg; 
    arg = SCmd.next(); 
    
    if (arg != NULL) {

      //Complete newZowiName char string
      int k = 0;
      while((*arg) && (k<11)){ 
          newZowiName[k]=*arg++;
          k++;
      }
      
      EEPROM.put(eeAddress, newZowiName); 
    }
    else 
    {
      delay(2000);
    }

    sendFinalAck();

}


//-- Function to send Zowi's name
void requestName(){

    zowi.home(); //stop if necessary

    char actualZowiName[11]= "";  //Variable to store data read from EEPROM.
    int eeAddress = 5;            //EEPROM address to start reading from

    //Get the float data from the EEPROM at position 'eeAddress'
    EEPROM.get(eeAddress, actualZowiName);

    Serial.print(F("&&"));
    Serial.print(F("E "));
    Serial.print(actualZowiName);
    Serial.println(F("%%"));
    Serial.flush();
}


//-- Function to send ultrasonic sensor measure (distance)
void requestDistance(){

    zowi.home();  //stop if necessary  

    int distance = zowi.getDistance();
    Serial.print(F("&&"));
    Serial.print(F("D "));
    Serial.print(distance);
    Serial.println(F("%%"));
    Serial.flush();
}


//-- Function to send noise sensor measure
void requestNoise(){

    zowi.home();  //stop if necessary

    int microphone= zowi.getNoise(); //analogRead(PIN_NoiseSensor);
    Serial.print(F("&&"));
    Serial.print(F("N "));
    Serial.print(microphone);
    Serial.println(F("%%"));
    Serial.flush();
}

//-- Function to send program ID
void requestProgramId(){

    zowi.home();   //stop if necessary

    Serial.print(F("&&"));
    Serial.print(F("I "));
    Serial.print(programID);
    Serial.println(F("%%"));
    Serial.flush();
}


//-- Function to send Ack comand (A)
void sendAck(){

  delay(30);

  Serial.print(F("&&"));
  Serial.print(F("A"));
  Serial.println(F("%%"));
  Serial.flush();
}


//-- Function to send final Ack comand (F)
void sendFinalAck(){

  delay(30);

  Serial.print(F("&&"));
  Serial.print(F("F"));
  Serial.println(F("%%"));
  Serial.flush();
}



//-- Functions with animatics
//--------------------------------------------------------


void ZowiSleeping_withInterrupts(){

  int bedPos_0[4]={100, 80, 60, 120}; //{100, 80, 40, 140}

    zowi._moveServos(700, bedPos_0);  //800  
 

  for(int i=0; i<4;i++){

      zowi.bendTones (100, 200, 1.04, 10, 10);
    
      zowi.bendTones (200, 300, 1.04, 10, 10);  

      zowi.bendTones (300, 500, 1.04, 10, 10);   

    delay(500);
    
      zowi.bendTones (400, 250, 1.04, 10, 1); 
      zowi.bendTones (250, 100, 1.04, 10, 1); 
    
    delay(500);
  } 
  zowi.home();
}
