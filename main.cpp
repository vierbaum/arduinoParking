#include "main.h"
#include "motor.h"
#include "sensor.h"
#include "gprintf.h"


int mainfun() {
  Serial.begin(9600);

  // testing gprintf
  gprintf("Hello %\n", "world");

  // testing motor
  Motor m1;
  m1.init(5);
  m1.offset = 1;
  while(true)
    for(short i = 25; i <= 100; i++){
      m1.forward(i);
      delay(500);

    }

  // testing sensor
  Sensor s1;
  s1.init(2);
  while(true)
    Serial.println(s1.read());

  return 0;
}
