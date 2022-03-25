#define INP_PIN 13
#define OUT_FIN 12
#define INP_FIN 11

#include "Arduino.h"
class Receive {
public:
  void Init() {
    pinMode(INP_PIN, INPUT);
    pinMode(OUT_FIN, OUTPUT);
    pinMode(INP_FIN, INPUT);

    analogWrite(OUT_FIN, LOW);
  }

  // trivial
  int Think() {
     char* pInp = malloc(33); // minor runtime optimization!!!!!!!
     pInp[33] = 0;
     for (int i = 0; i < 33; i++) {
        while(digitalRead(INP_FIN) == 0){delay(1);};
        analogWrite(OUT_FIN, LOW);
        //Serial.print(analogRead(INP_PIN));
        Serial.print(digitalRead(INP_PIN));
        //pInp[i] = (char) digitalRead(INP_PIN);
        analogWrite(OUT_FIN, HIGH);
     }

     //Serial.print(pInp);
     Serial.println();
  }
};
