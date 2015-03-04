#include <Servo.h>
#include <Oscillator.h>

#define N_SERVOS 4

#define INTERVALTIME 10.0 

#define TRIM_RR -10
#define TRIM_RL -8
#define TRIM_YR 8
#define TRIM_YL 7

#define PIN_RR 4
#define PIN_RL 5 //8
#define PIN_YR 2
#define PIN_YL 3

Oscillator servo[N_SERVOS];

void goingUp(int tempo);
void drunk (int tempo);
void noGravity(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void run(int steps, int T=500);
void walk(int steps, int T=1000);
void backyard(int steps, int T=3000);
void backyardSlow(int steps, int T=5000);
void turnLeft(int steps, int T=3000);
void turnRight(int steps, int T=3000);
void moonWalkLeft(int steps, int T=1000);
void moonWalkRight(int steps, int T=1000);
void crusaito(int steps, int T=1000);
void swing(int steps, int T=1000);
void upDown(int steps, int T=1000);
void flapping(int steps, int T=1000);

void setup()
{
  Serial.begin(19200);
  
  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);
  
  servo[0].SetTrim(TRIM_RR);
  servo[1].SetTrim(TRIM_RL);
  servo[2].SetTrim(TRIM_YR);
  servo[3].SetTrim(TRIM_YL);
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);

  
}

// TEMPO: 121 BPM
int t=495;
double pause=0;

void loop()
{
  if(Serial.available()){
    char init = Serial.read();
    if (init=='X'){
      delay(4000); //3000 - 4500
      dance();
    }
  }
}

void dance(){
  primera_parte();
  segunda_parte();
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  primera_parte(); //otra vez
  crusaito(1,t*8);
  crusaito(1,t*7);

  for (int i=0; i<16; i++){
    flapping(1,t/4);
    delay(3*t/4);
  }
 
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);

  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  kickLeft(t);
  kickRight(t);
  drunk(t*8);
  drunk(t*4);
  drunk(t/2);
  delay(t*4); 

  drunk(t/2);

  delay(t*4); 
  walk(2,t*2);//Javi del futuro sigue aqui
  backyard(2,t*2);//Javi del futuro sigue aqui
  goingUp(t*2);
  goingUp(t*1);
  noGravity(t*2);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*8);/**/
  crusaito(1,t*2);
  crusaito(1,t*3);

  delay(t);
  primera_parte();
    for (int i=0; i<32; i++){
    flapping(1,t/2);
    delay(t/2);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);


}




//////////////////////////////////////////////////////////////////////////////
/////////////////////////////FUNCIONES DE CONTROL/////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS]; 
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++)	increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  
  final_time =  millis() + time; 
  
  iteration = 1; 
  while(millis() < final_time){ //Javi del futuro cambia esto  
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time){	  
          if(oneTime<1){ 
              for(int i=0;i<N_SERVOS;i++){
                  servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }			
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++){	
    oldPosition[i] = newPosition[i];
  }   
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void goingUp(int tempo){
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      delay(tempo);
      servo[0].SetPosition(80);
      servo[1].SetPosition(100);
      delay(tempo);
      servo[0].SetPosition(70);
      servo[1].SetPosition(110);
      delay(tempo);
      servo[0].SetPosition(60);
      servo[1].SetPosition(120);
      delay(tempo);
      servo[0].SetPosition(50);
      servo[1].SetPosition(130);
      delay(tempo);
      servo[0].SetPosition(40);
      servo[1].SetPosition(140);
      delay(tempo);
      servo[0].SetPosition(30);
      servo[1].SetPosition(150);
      delay(tempo);
      servo[0].SetPosition(20);
      servo[1].SetPosition(160);
      delay(tempo);
      
      while(millis()<pause+8*t);
      



}

void primera_parte(){
  for(int x=0; x<3; x++){
    for(int i=0; i<3; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    moveNServos(t*0.4,(int[]){60,120,90,90});
    moveNServos(t*0.4,(int[]){90,90,90,90});
    while(millis()<(pause+t*2));
  }
  
   for(int i=0; i<2; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    crusaito(1,t*1.4);
    moveNServos(t*1,(int[]){40,140,90,90});
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    while(millis()<(pause+t*4));
 
}

void segunda_parte(){
  for(int x=0; x<7; x++){
  for(int i=0; i<3; i++){
    pause=millis();
    moveNServos(t*0.15,(int[]){90,90,80,100});
    moveNServos(t*0.15,(int[]){90,90,100,80});
    moveNServos(t*0.15,(int[]){90,90,80,100});
    moveNServos(t*0.15 ,(int[]){90,90,100,80});
    while(millis()<(pause+t));
  }
  pause=millis();
  moveNServos(t*0.15,(int[]){40,140,80,100});
  moveNServos(t*0.15,(int[]){40,140,100,80});
  moveNServos(t*0.15,(int[]){90,90,80,100});
  moveNServos(t*0.15 ,(int[]){90,90,100,80});
  while(millis()<(pause+t));
  }
 
  for(int i=0; i<3; i++){

    pause=millis();
    moveNServos(t*0.15,(int[]){40,140,80,100});
    moveNServos(t*0.15,(int[]){40,140,100,80});
    moveNServos(t*0.15,(int[]){90,90,80,100});
    moveNServos(t*0.15 ,(int[]){90,90,100,80});
    while(millis()<(pause+t));
  }
}

void lateral_fuerte(boolean side, int tempo){
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo/2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/2);

}

void drunk (int tempo){
  pause=millis();
  moveNServos(tempo*0.235,(int[]){60,70,90,90});
  moveNServos(tempo*0.235,(int[]){110,120,90,90});
  moveNServos(tempo*0.235,(int[]){60,70,90,90});
  moveNServos(tempo*0.235,(int[]){110,120,90,90});
  while(millis()<(pause+tempo));

}


void noGravity(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,(int[]){120,140,90,90});
  moveNServos(tempo*2,(int[]){140,140,90,90});
  delay(tempo*2);
  moveNServos(tempo*2,(int[]){120,140,90,90});
  moveNServos(tempo*2,(int[]){90,90,90,90});

 

}

void kickLeft(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

void kickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0] + 10, A[1] - 10, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
