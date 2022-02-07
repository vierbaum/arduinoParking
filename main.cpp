#include "main.h"
#include "motor.h"

using namespace std;

int mainfun() {
  Serial.begin(9600);
  Serial.println("Test");

  Motor m1;
  m1.init(5);
  while(true)
    for(int s = 0; s <= 255; s++)
      m1.forward(200);

  return 0;
}
