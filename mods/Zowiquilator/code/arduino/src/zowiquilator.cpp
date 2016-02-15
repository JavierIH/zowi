#include <Arduino.h>
#include <Servo.h>
#include <Oscillator.h>

#define N_OSCILLATORS 9

#define TRIM_ROLLRIGHT -6 //-11
#define TRIM_ROLLLEFT -10//-17
#define TRIM_YAWRIGHT -17//-13
#define TRIM_YAWLEFT -10//-6
#define TRIM_SHOULDERRIGHT 43//15
#define TRIM_SHOULDERLEFT -34//0
#define TRIM_ARMRIGHT 7//6
#define TRIM_ARMLEFT -9//0
#define TRIM_HEAD 10//0


#define PIN_ROLLRIGHT 4
#define PIN_ROLLLEFT 5
#define PIN_YAWRIGHT 6
#define PIN_YAWLEFT 7
#define PIN_SHOULDERRIGHT 2
#define PIN_SHOULDERLEFT 8
#define PIN_ARMRIGHT 3
#define PIN_ARMLEFT 9
#define PIN_HEAD 12

Oscillator osc[N_OSCILLATORS];

void run(int steps=1, int T=500);
void walk(int steps=1, int T=1000);
void backward(int steps=1, int T=1000);
void turnL(int steps=1, int T=1000);
void turnR(int steps=1, int T=1000);
void moonWalkL(int steps=1, int T=1000);
void moonWalkR(int steps=1, int T=1000);
void upDown(int steps=1, int T=700);
void home();
void attack();
void punchL();
void punchR();
void yesyes();

void setup()
{
    Serial.begin(19200);

    pinMode(13, OUTPUT);

    osc[0].attach(PIN_ROLLRIGHT);
    osc[1].attach(PIN_ROLLLEFT);
    osc[2].attach(PIN_YAWRIGHT);
    osc[3].attach(PIN_YAWLEFT);
    osc[4].attach(PIN_SHOULDERRIGHT);
    osc[5].attach(PIN_SHOULDERLEFT);
    osc[6].attach(PIN_ARMRIGHT);
    osc[7].attach(PIN_ALEFT);/**/
    osc[8].attach(PIN_HEAD);/**/

    osc[0].SetTrim(TRIM_ROLLRIGHT);
    osc[1].SetTrim(TRIM_ROLLLEFT);
    osc[2].SetTrim(TRIM_YAWRIGHT);
    osc[3].SetTrim(TRIM_YAWLEFT);
    osc[4].SetTrim(TRIM_SHOULDERRIGHT);
    osc[5].SetTrim(TRIM_SHOULDERLEFT);
    osc[6].SetTrim(TRIM_ARMRIGHT);
    osc[7].SetTrim(TRIM_ARMLEFT);/**/
    osc[8].SetTrim(TRIM_HEAD);/**/

    digitalWrite(13, HIGH);
    home();

}

char input;

void loop()
{
    if(Serial.available()){
        while (Serial.available()) input = Serial.read();
        switch(input){
            case 'A':
                walk();
                break;

            case 'B':
                turnR();
                break;

            case 'C':
                backward();
                break;

            case 'D':
                turnL();
                break;

            case 'E':
                upDown();
                break;

            case 'F':
                punchR();
                delay(300);
                break;

            case 'G':
                attack();
                delay(300);
                break;

            case 'H':
                punchL();
                delay(300);
                break;

            case 'I':
                moonWalkL();
                break;

            case 'J':
                yesyes();
                break;
            default:
                home();
                break;
        }
        Serial.flush();
    }
    else home();
}


void oscillate(int A[N_OSCILLATORS], int O[N_OSCILLATORS], int T, double phase_diff[N_OSCILLATORS]){
  for (int i=0; i<8; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(T);
    osc[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<8; i++){
        osc[i].refresh();
     }
  }
}

void oscillate_mod(int A[N_OSCILLATORS], int O[N_OSCILLATORS], int Ta , int Tb, double phase_diff[N_OSCILLATORS]){
  for (int i=0; i<2; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(Ta);
    osc[i].SetPh(phase_diff[i]);
  }
  for (int i=2; i<4; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(Tb);
    osc[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<Tb+ref; x=millis()){
     for (int i=0; i<4; i++){
        osc[i].refresh();
     }
  }
}

void walk(int steps, int T){
    int A[8]= {15, 15, 25, 25, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnR(int steps, int T){
    int A[8]= {15, 15, 10, 30, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnL(int steps, int T){
    int A[8]= {15, 15, 30, 10, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void backward(int steps, int T){
    int A[8]= {15, 15, 25, 25, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(90), DEG2RAD(90), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void moonWalkR(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 10, 10};
    int O[8] = {-15, 15, 0, 0, 60, -60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(180), DEG2RAD(180), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkL(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 20, 20};
    int O[8] = {-15, 15, 0, 0, 60, -60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(0), DEG2RAD(0), DEG2RAD(0), DEG2RAD(0)};


    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 35, 35};
    int O[8] = {-25, 25, 0, 0, -60, 60, 0, 0,};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180), 0, 0,
                            0, 0, DEG2RAD(0), DEG2RAD(180)};

    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void home(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(50);
    osc[7].SetPosition(130);
    osc[8].SetPosition(90);

}

void attack(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(90);
    osc[5].SetPosition(90);
    osc[6].SetPosition(40);
    osc[7].SetPosition(140);
}

void punchL(){
    osc[0].SetPosition(40);
    osc[1].SetPosition(70);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(90);
    osc[7].SetPosition(30);
}

void punchR(){
    osc[0].SetPosition(110);
    osc[1].SetPosition(140);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(150);
    osc[7].SetPosition(90);
}

void yesyes(){
    home();
    for (int i=0; i<4; i++){
        osc[8].SetPosition(90);
        for (int j=0; j<3; j++){
            digitalWrite(13, HIGH);
            delay(25);
            digitalWrite(13, LOW);
            delay(25);
        }
        osc[8].SetPosition(130);
        for (int j=0; j<3; j++){
            digitalWrite(13, HIGH);
            delay(25);
            digitalWrite(13, LOW);
            delay(25);
        }
    }
    digitalWrite(13, HIGH);
}
