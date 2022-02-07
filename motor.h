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

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(speedpin, OUTPUT);
  }

  void forward(short speed) {
    Serial.println(pin1);
    Serial.println(pin2);
    Serial.println(speedpin);
    Serial.println(speed);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedpin, speed);
  }

  void backward(short speed) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedpin, speed);
  }

  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(speedpin, LOW);
  }
};

#endif // MOTOR_H_
