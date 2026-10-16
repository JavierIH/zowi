#include <Zowi.h>
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

Zowi zowi;
int echo = 8;
int trigger = 9;
int buttonL = 0;
int buttonR = 1;

void baile() {
  int tempo = 130;
  int ligue = 40;
  tone(6, 880);
  delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 880);
  delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 880);
  delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 880);
  delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 785);
  delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 880);
  delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 988);
  zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 988);
  zowi.jump(1, tempo - ligue);
  noTone(6);
  delay(tempo * 2);
  tone(6, 880); delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 988); delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 1047);   zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 1047);   zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  delay(tempo * 2);
  tone(6, 988); delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 1047); delay(tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 988);   zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 784);   zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 659);   zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  tone(6, 880);   zowi.jump(1, tempo - ligue);
  noTone(6); delay(ligue);
  delay(tempo * 2);
}

void navegar() {
  float dist;
  int ok = 0;
  delay(600);
  for (int i = 0; i < 3 && ok != 1; i++) {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    dist = pulseIn(echo, HIGH);
    //Serial.println(dist);
    if (dist != 0) ok = 1;
  }

  if (dist < 1000 && dist != 0) {
    zowi.turnLeft(2, 1000);
    tone(6, 400, 50);
  }
  else {

    for (int i = 0; i < 2; i++) {
      zowi.walk(0.5, 1000);
      tone(6, 300, 50);
      zowi.walk(0.5, 1000);
      tone(6, 400, 50);
    }
  }
}

  int channel[2];
  int pos[] = {90, 90, 90, 90};

void swing() {
  
  if (Serial.available() > 3) {
    while (Serial.read() != 0);
    for (int i = 0; i < 2; i++) channel[i] = ((int)Serial.read());
    pos[3] = channel[1];
    pos[2] = channel[1];
    pos[1] = channel[0];
    pos[0] = channel[0];
    zowi.moveServos(0, pos);
  }
}

void micro() {
  if (!digitalRead(7)) {
    pos[3] = 70;
    pos[2] = 110;
    pos[1] = 90;
    pos[0] = 90;
    zowi.moveServos(0, pos);
    delay(100);
  }
  else{
      pos[3] = 90;
    pos[2] = 90;
    pos[1] = 90;
    pos[0] = 90;
    zowi.moveServos(0, pos);
  }
  
}

void setup()
{
  int t = 495;
  zowi.init(2, 3, 4, 5, 1);
  //zowi.setTrims(-17,-6,5,0);
  //zowi.saveTrimsOnEEPROM();

  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(buttonL, INPUT);
  pinMode(buttonR, INPUT);


  Serial.begin(19200);

}

int posiciones[] = {90, 90, 90, 90};
int posiciones2[] = {80, 80, 80, 80};
long ex_t=0;
void loop()
{
  
  zowi.walk(0.5,800);
  //zowi.moveServos(0,posiciones); 
 /* zowi.moveServos(0, posiciones);


  tone(6, 400);
  zowi.jump(1, 50);
  tone(6, 1000); delay(50);
  tone(6, 400);
  zowi.jump(1, 50);
  tone(6, 1000); delay(50);
  noTone(6);
  delay(200);


  int buttonR_pressed = 0;
  int program = 0;
  while (!buttonR_pressed) {
    if (!digitalRead(buttonL)) {
      tone(6, 1000, 50);
      delay(200);
      program++;
      if (program > 3) program = 0;
      //Serial.println(program);

    }
    buttonR_pressed = !digitalRead(buttonR);
  }
  for (int x = 0; x < 50; x++) {
    tone(6, random(50, 3000));
    delay(50);
  }
  noTone(6);
  delay(1000);

  switch (program) {
    case 0:
      baile();
      break;
    case 1:
      for (int x = 0; x < 14; x++)navegar();
      break;
    case 2:
      ex_t=millis();
      while(millis()<ex_t+20000) micro();
      break;
    case 3:
      //do something when var equals 2
      break;

  }

/**/

/*
  if (Serial.available() > 3) {
    while (Serial.read() != 0);
    for (int i = 0; i < 2; i++) channel[i] = ((int)Serial.read());
    pos[3] = channel[1]+45;
    pos[2] = channel[1]+45;
    pos[1] = channel[0]+45;
    pos[0] = channel[0]+45;
    zowi.moveServos(0, pos);
  }/**/
}

