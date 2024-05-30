#include "ESP32_IDE.h"

#define canal_a1  E6
#define canal_b1  E7
#define canal_a2  E8
#define canal_b2  E9
#define canal_a3  E10
#define canal_b3  E11

#define dir1  S7
#define dir2  S9
#define dir3  S11
#define pwm1  S6
#define pwm2  S8
#define pwm3  S10

int sensor01;
int sensor02;

int stepOld;
int step;

float PulseCount = 0;
long PulsePost;

void checkState(){
  /* sensor01 = digitalRead(canal_a1);
  sensor02 = digitalRead(canal_b1);
 */
  PulseCount += 0.01;
  /* if(sensor01 == 1 && sensor02 == 1){
    step = 0;
    if(stepOld == 1){
      PulseCount--;
    }
    if(stepOld == 3){
      PulseCount++;
    }
    stepOld = 0;
  }

  if(sensor01 == 0 && sensor02 == 1){
    step = 1;
    if(stepOld == 2){
      PulseCount--;
    }
    if(stepOld == 0){
      PulseCount++;
    }
    stepOld = 1;
  }

  if(sensor01 == 0 && sensor02 == 0){
    step = 2;
    if(stepOld == 3){
      PulseCount--;
    }
    if(stepOld == 1){
      PulseCount++;
    }
    stepOld = 2;
  }

  if(sensor01 == 1 && sensor02 == 0){
    step = 3;
    if(stepOld == 0){
      PulseCount--;
    }
    if(stepOld == 2){
      PulseCount++;
    }
    stepOld = 3;
  }
 */
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dir1, OUTPUT);
  pinMode(pwm1, OUTPUT); 
  pinMode(dir2, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(pwm3, OUTPUT);

  pinMode(canal_a1,INPUT);
  pinMode(canal_b1,INPUT);
  pinMode(canal_a2,INPUT);
  pinMode(canal_b2,INPUT);
  pinMode(canal_a3,INPUT);
  pinMode(canal_b3,INPUT);

  attachInterrupt(digitalPinToInterrupt(canal_a1), checkState, CHANGE);
  attachInterrupt(digitalPinToInterrupt(canal_b1), checkState, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(dir1, HIGH);
  analogWrite(pwm1, 100);
/*   delay(1000);
  digitalWrite(dir1, LOW);
  analogWrite(pwm1, 100);
  delay(1000); */

/*   PulsePost=(PulseCount/4);

  if(PulsePost > -1){
    Serial.print(" ");
  }

  if(PulsePost< 10 && PulsePost > -10){
    Serial.print(" ");
  }

  if(PulsePost < 100 && PulsePost > -100){
    Serial.print(" ");
  } */

  Serial.println(PulseCount);
}
