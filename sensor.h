#ifndef SENSOR_H_
#define SENSOR_H_
#include "Arduino.h"
#define MAGICNUMBER 0.03432

class Sensor {
  public:
    short trigger;
    short echo;

    void init(short pin) {
      // set pins
      echo = pin;
      trigger = pin + 1;

      pinMode(trigger, OUTPUT);
      pinMode(echo, INPUT);
    }

  // brendom moment
  double read () {
    digitalWrite(trigger, LOW);
    delay(5);
    digitalWrite(trigger, HIGH);
    delay(10);
    digitalWrite(trigger, LOW);
    // calculating distance
    double duration = pulseIn(echo, HIGH);
    double distance = (duration / 2) * MAGICNUMBER;
    delay(300);
    return distance;
  }
};

#endif // SENSOR_H_
