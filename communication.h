#include <Wire.h>
/* MASTER */
#define NODE_MAX_NUMBER 5
#define PAYLOAD_SIZE 2
int nodePayload[NODE_MAX_NUMBER][PAYLOAD_SIZE];

#include "Arduino.h"
void Transmit(int receiver, byte data) {
    Wire.beginTransmission(receiver);
    Wire.write(data);
    Wire.endTransmission();
}

void Request(int source) {
    Wire.requestFrom(source, PAYLOAD_SIZE);
      if (Wire.available() == PAYLOAD_SIZE) {        
        for (int i = 0; i < PAYLOAD_SIZE; i++) {
          nodePayload[source][i] = Wire.read();   
          Serial.println(nodePayload[source][i]); 
        }
    }  
}

#define NODE_ADDRESS 2
#define PAYLOAD_SIZE 2
byte nodePayloadSlave[PAYLOAD_SIZE];

void requestEvent() {
  nodePayloadSlave[0] = NODE_ADDRESS;
  nodePayloadSlave[1] = analogRead(A0) / 4;
  Wire.write(nodePayloadSlave, PAYLOAD_SIZE);
}

void receiveEvent(int bytes) {
  int x = 0;
  x = Wire.read();
  Serial.println(x);
}
