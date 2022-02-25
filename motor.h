#ifndef MOTOR_H_
#define MOTOR_H_
#include "Arduino.h"

class Motor {
  public:
    short pin1;
    short pin2;
    short speedpin;
    float offset;

  void init(short pin) {
    // set pins
    pin1 = pin;
    pin2 = pin + 1;
    speedpin = pin + 2;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(speedpin, OUTPUT);
  }

  void forward(short speed) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    // convert % to abs
    analogWrite(speedpin, (int)(255 * ((float)speed / 100) * offset));
  }

  void backward(short speed) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedpin, (int)(255 * ((float)speed / 100) * offset));
  }

  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(speedpin, LOW);
  }
};

#endif // MOTOR_H_
