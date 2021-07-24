#define MOTOR_A_PIN 8
#define MOTOR_B_PIN 9
#define MOTOR_ENABLE_PIN 5
#define POTENTIOMETER_PIN A0
#define BUTTON_NEXT_PIN 6
#define BUTTON_PREVIOUS_PIN 7


#define FADER_MIN 100
#define FADER_MAX 900
#define TOLERANCE 6

#include "MotorFader.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

MotorFader motorFader(MOTOR_A_PIN, MOTOR_B_PIN, MOTOR_ENABLE_PIN, POTENTIOMETER_PIN, FADER_MIN, FADER_MAX, TOLERANCE);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int lastVolume = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
}

void loop(){
  int vol = getVolume();
  while((!digitalRead(BUTTON_NEXT_PIN) && !digitalRead(BUTTON_PREVIOUS_PIN)) && vol == lastVolume){
    vol = getVolume();
  }
  if (digitalRead(BUTTON_NEXT_PIN)){
    while (digitalRead(BUTTON_NEXT_PIN)){
      delay(50);
    }
    Serial.print('b');
    Serial.print(1);
  } else if(digitalRead(BUTTON_PREVIOUS_PIN)){
    while(digitalRead(BUTTON_PREVIOUS_PIN)){
      delay(50);
    }
    Serial.print('b');
    Serial.print(2);
  } else if (vol != lastVolume){
    Serial.print('b');
    Serial.print(0);
    Serial.write(vol);
    printVolume(vol);
    lastVolume = vol;
    delay(50);
    return;
  }
  String rec = Serial.readStringUntil('\n');

  if (getValue(rec,';',0) != "v"){
    return;
  }
  int volume = getValue(rec,';',1).toInt();
  motorFader.ToPos(volume);
  if (getValue(rec,';',2) != "a"){
    return;
  }
  printApp(getValue(rec,';',3), volume);
  lastVolume = volume;

}

int getVolume(){
  int vol = map(analogRead(POTENTIOMETER_PIN), FADER_MIN, FADER_MAX, 0, 100);
  if (vol > 100){
      vol = 100;
  } else if (vol < 0){
    vol = 0;
  }
  return vol;
}

void printApp(String app, int volume){
  lcd.flush();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(app);
  lcd.setCursor(0,1);
  lcd.print(String(volume));
}

void printVolume(int volume){
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print(String(volume));
}

String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
