#ifndef MOTORFADER_H
#define MOTORFADER_H
#include <Arduino.h>

class MotorFader {
  private:
    int motor_pin_a;
    int motor_pin_b;
    int enable_pin;
    int potentiometer_pin;
    int faderMin;
    int faderMax;
    int tolerance;
    int faderSpeed[3] = {255, 150, 100};
    int faderSpeedDist[2] = {600, 100};
  public:
    MotorFader(int motor_pin_a, int motor_pin_b, int enable_pin, int potentiometer_pin, int faderMin, int faderMax, int tolerance);

    int GetFaderMin();

    int GetFaderMax();

    int GetFaderTolerance();

    int GetFaderMinTarget(int target);
    
    int GetFaderMaxTarget(int target);

    int GetPos();

    int GetTarget(int target);

    void SetFaderSpeed(int val);

    void ToPos(int target);

    void MotorUp();

    void MotorDown();

    void MotorStop();
};
#endif