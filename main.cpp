#include "main.h"
#include "motor.h"
#include "sensor.h"

using namespace std;

int mainfun() {
  Serial.begin(9600);
  Serial.println("Test");

  Motor m1;
  m1.init(5);
  //while(true)
  //  m1.forward(200);

  Sensor s1;
  s1.init(2);
  while(true)
    Serial.println(s1.read());

  return 0;
}
