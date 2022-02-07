#ifndef SENSOR_H_
#define SENSOR_H_
#include "Arduino.h"
#define MAGICNUMBER 0.03432

class Sensor {
  public:
    short trigger;
    short echo;

    void init(short pin) {
      echo = pin;
      trigger = pin + 1;

      pinMode(trigger, OUTPUT);
      pinMode(echo, INPUT);
    }

  double read () {
    double duration;
    double distance;
    digitalWrite(trigger, LOW);
    delay(5);
    digitalWrite(trigger, HIGH);
    delay(10);
    digitalWrite(trigger, LOW);
    duration = pulseIn(echo, HIGH);
    distance = (duration / 2) * MAGICNUMBER;
    delay(300);
    return distance;
  }

};

#endif // SENSOR_H_
