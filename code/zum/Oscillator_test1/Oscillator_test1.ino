#include <Servo.h>
#include <Oscillator.h>

#define N_OSCILLATORS 4

#define TRIM_RR -4
#define TRIM_RL -4
#define TRIM_YR -12
#define TRIM_YL -2

#define PIN_RR 9
#define PIN_RL 5 //8
#define PIN_YR 2
#define PIN_YL 3

Oscillator osc[N_OSCILLATORS];

void run(int steps, int T=500);
void walk(int steps, int T=1000);
void backyard(int steps, int T=3000);
void backyardSlow(int steps, int T=5000);
void turnLeft(int steps, int T=3000);
void turnRight(int steps, int T=3000);
void moonWalkerLeft(int steps, int T=1000);
void moonWalkerRigh(int steps, int T=1000);
void crusaito(int steps, int T=1000);
void swing(int steps, int T=1000);
void upDown(int steps, int T=1000);
void flapping(int steps, int T=1000);

void setup()
{
  osc[0].attach(PIN_RR);
  osc[1].attach(PIN_RL);
  osc[2].attach(PIN_YR);
  osc[3].attach(PIN_YL);
  
  osc[0].SetTrim(TRIM_RR);
  osc[1].SetTrim(TRIM_RL);
  osc[2].SetTrim(TRIM_YR);
  osc[3].SetTrim(TRIM_YL);
}

void loop()
{
   int A[4]= {35, 10, 16, 16};
   int O[4] = {-10, 10, 0, 0};
   double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(180), DEG2RAD(00)};
   int T=3000;
    
   while(1) oscillate(A,O, T, phase_diff);
   /*int a=10;
   int t=200;
   
  osc[0].SetPosition(30);
  osc[1].SetPosition(150);
  osc[2].SetPosition(90-a);
  osc[3].SetPosition(90+a);
  
  delay(t);
  
  osc[0].SetPosition(30);
  osc[1].SetPosition(150);
  osc[2].SetPosition(90+a);
  osc[3].SetPosition(90-a);
  
  delay(t);
 
  osc[0].SetPosition(50);
  osc[1].SetPosition(130);
  osc[2].SetPosition(90+a);
  osc[3].SetPosition(90-a);
  
  delay(t); 
  
  osc[0].SetPosition(50);
  osc[1].SetPosition(130);
  osc[2].SetPosition(90-a);
  osc[3].SetPosition(90+a);
  
  delay(t);*/
}


void oscillate(int A[N_OSCILLATORS], int O[N_OSCILLATORS], int T, double phase_diff[N_OSCILLATORS]){
  for (int i=0; i<4; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(T);
    osc[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
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
    int A[4]= {15, 15, 30, 30};
    int O[4] = {TRIM_RR, TRIM_RL, TRIM_YR, TRIM_YL};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {-18, 7, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {-18, 7, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {-18, 7, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void turnRight(int steps, int T){
    int A[4]= {15, 15, 10, 30};
    int O[4] = {-18, 7, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnLeft(int steps, int T){
    int A[4]= {15, 15, 30, 10};
    int O[4] = {-18, 7, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-18 - 15, 7 + 15, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-18 - 15, 7 + 15, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {-18 - 15, 7 + 15, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-18 - 15, 7 + 15, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-18 - 15, 7 + 15, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-18 - A[0] + 10, 7 + A[1] - 10, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-18 - A[0] + 10, 7 + A[1] - 10, -6, -11};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
