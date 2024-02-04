#include "piComm.h"

piComm pi(Serial1);

void setup() {
  pi.init();
  Serial.begin(152000);  //init Serial
}

int count = 2;

void loop() {
  if (pi.msgWaiting()) {
    auto [success, data] = pi.read();

    if (success) {
      if (!count--) {
        Serial.printf("(%d,%s)\n", success, data.c_str());
        count = 100;
      }
      pi.send(data);
    } else {
      Serial.printf("(%d,None)\n", success);
      while (1)
        ;
    }
  }
}