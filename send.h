#define OUT_PIN 13
#define INP_FIN 12
#define OUT_FIN 11

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
    char* binary = (char*)malloc(17);
    binary[17] = 0;
    int mask = 1;
    // looping through array
    for(int i = 16; i != 0; i--) {
    if((mask&a) >= 1)
        binary[i] = '1';
    else
        binary[i] = '0';
     mask<<=1;
    }

    // send number
    for (int i = 0; i < 17; i++) {
      // transfer first number anyways
      if (i == 0) {
        bool bTransfer = binary[i] == '0' ? false : true;
        digitalWrite(OUT_PIN, bTransfer);
        digitalWrite(OUT_FIN, HIGH);
        continue;
      }

      // else only transfer when other arduino is ready
      if (digitalRead(INP_FIN) == HIGH) {
        digitalWrite(OUT_FIN, LOW);
        bool bTransfer = binary[i] == '0' ? false : true;
        digitalWrite(OUT_PIN, bTransfer);
        digitalWrite(OUT_FIN, HIGH);
      }
    }
  }
};
