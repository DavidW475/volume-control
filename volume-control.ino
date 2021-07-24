#define MOTOR_A_PIN 8
#define MOTOR_B_PIN 9
#define MOTOR_ENABLE_PIN 5
#define POTENTIOMETER_PIN A0


#define FADER_MIN 100
#define FADER_MAX 900
#define TOLERANCE 10

#include "MotorFader.h"

int faderSpeed[] = {255, 150, 100};

MotorFader motorFader(MOTOR_A_PIN, MOTOR_B_PIN, MOTOR_ENABLE_PIN, POTENTIOMETER_PIN, FADER_MIN, FADER_MAX, TOLERANCE);

void setup() {
  Serial.begin(9600);
  
}

void loop(){
  motorFader.ToPos(50);
  delay(1000);
  motorFader.ToPos(100);
  delay(1000);
  motorFader.ToPos(0);
  delay(1000);
  motorFader.ToPos(25);
  delay(1000);
  motorFader.ToPos(75);
  delay(1000);
}

void faderPosition(int pos){
  int currentPos = analogRead(POTENTIOMETER_PIN);
  int targetPos = map(pos, 0, 100, FADER_MIN, FADER_MAX);
  analogWrite(MOTOR_ENABLE_PIN, faderSpeed[1]);
  int targetMin = targetPos - TOLERANCE;
  int targetMax = targetPos + TOLERANCE;
  int i = 0;
  while ((currentPos < targetMin || currentPos > targetMax) || i < 100){
    if (currentPos < targetMin){
      motorUp();
      i=0;
    } else if (currentPos > targetMax){
      motorDown();
      i=0;
    }else{
      i++;
    }
    currentPos = analogRead(POTENTIOMETER_PIN);
  }
  motorStop();
}

void motorUp(){
  digitalWrite(MOTOR_A_PIN, HIGH);
  digitalWrite(MOTOR_B_PIN, LOW);
}

void motorDown(){
  digitalWrite(MOTOR_A_PIN, LOW);
  digitalWrite(MOTOR_B_PIN, HIGH);
}

void motorStop(){
  digitalWrite(MOTOR_A_PIN, LOW);
  digitalWrite(MOTOR_B_PIN, LOW);
  analogWrite(MOTOR_ENABLE_PIN, 0);
}
