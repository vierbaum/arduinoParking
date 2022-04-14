#include "main.h"
#include "motor.h"
#include "sensor.h"
#include "gprintf.h"
#include "communication.h"

#define IS_MASTER false

int mainfun() {
  Serial.begin(9600);

  Sensor s1;

  Motor mL;
  Motor mR;
  if(IS_MASTER) {
    s1.init(8);
  } else {
    mL.init(5);
    mR.init(8);
  }
  short cPD;

  mainloop:
    if (IS_MASTER){
      Wire.begin();
      Serial.println(s1.read());
      Transmit(NODE_ADDRESS, (int)s1.read());
      Request(NODE_ADDRESS);
    } else {
      Wire.begin(NODE_ADDRESS);
      Wire.onReceive(receiveEvent);
      Wire.onRequest(requestEvent);

      Serial.print("cD");
      Serial.println(cD);

      /*
      mL.forward(50);
      mR.forward(50);

      // checking for parking space
      if (cD > 40) {
        // driving until fully alongside
        delay(500);
        mL.backward(50);
        mR.forward(50);
        delay(200);
        mL.forward(50);
        delay(400);
        mL.forward(50);
        mR.backward(50);
        exit(1);
      }
      // checking if steering to the right or distance too high
      if (cD - cPD > 0 || cD > 10){
        // steering left
        mR.forward(55);
      } else if (cD - cPD < 0 || cD < 7) {
        mL.forward(55);
      }*/
    }
  goto mainloop;
  return 0;
}
