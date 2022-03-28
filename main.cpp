#include "main.h"
#include "motor.h"
#include "sensor.h"
#include "gprintf.h"
#include "communication.h"

#define IS_MASTER true

int mainfun() {
  Sensor s1;
  s1.init(2);
  
  Serial.begin(9600);
  if (IS_MASTER) {
    Wire.begin();
    while (true) {
      Serial.print("SENSOR ");
      Serial.println(s1.read());
      Transmit(NODE_ADDRESS, (int)s1.read());
      Request(NODE_ADDRESS);
    }
  }
  else {
    Wire.begin(NODE_ADDRESS);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
  
    while(true) {
      delay(10);
    } 
  }
  
  // testing gprintf
  gprintf("Hello %\n", "world");

  return 0;
}
