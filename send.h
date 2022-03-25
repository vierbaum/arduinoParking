#define OUT_PIN 13
#define INP_FIN 12
#define OUT_FIN 11

#include "Arduino.h"
class Send {
  public:
  void Init() {
    pinMode(OUT_PIN, OUTPUT);
    pinMode(INP_FIN, INPUT);
    pinMode(OUT_FIN, OUTPUT);
  }

  void Think(int iSendNum) {
    //binary
    int a=iSendNum;
    // basic char-pointer-array
    short* binary = (short*)malloc(33);
    binary[33] = 0;
    int mask = 1;
    // looping through array
    for(int i = 32; i != 0; i--) {
      if((mask&a) >= 1)
          binary[i] = 255;
      else
          binary[i] = 0;
        mask<<=1;
    }
    Serial.println();


    // send number
    for (int i = 0; i < 33; i++) {
      Serial.println(binary[i]);
      // transfer when other arduino is ready
      while(analogRead(INP_FIN) > 200){delay(1);};
      analogWrite(OUT_FIN, LOW); 
      analogWrite(OUT_PIN, binary[i]);
      analogWrite(OUT_FIN, HIGH);
    }
  }
};
