#define INP_PIN 13
#define OUT_FIN 12
#define INP_FIN 11

class Receive {
  void Init() {
    pinMode(INP_PIN, INPUT);
    pinMode(OUT_FIN, OUTPUT);
    pinMode(INP_FIN, INPUT);

    digitalWrite(OUT_FIN, LOW);
  }

  // trivial
  int Think() {
     char* pInp = malloc(17); // major runtime optimization!!!!!!!
     pInp[17] = 0;
     for (int i = 0; i < 17; i++) {
        digitalWrite(OUT_FIN, LOW);
        while(digitalRead(INP_FIN) == LOW);
        pInp[i] = digitalRead(INP_PIN);
        digitalWrite(OUT_FIN, HIGH);
     }
  }
};
