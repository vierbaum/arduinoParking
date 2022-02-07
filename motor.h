#ifndef MOTOR_H_
#define MOTOR_H_
#include "Arduino.h"

class Motor {
  public:
    short pin1;
    short pin2;
    short speedpin;

  void init(short pin) {
    pin1 = pin;
    pin2 = pin + 1;
    speedpin = pin + 2;
  }

  void forward(char speed) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedpin, speed);
  }
};

#endif // MOTOR_H_
