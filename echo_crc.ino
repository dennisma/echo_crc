#include "piComm.h"
#include <string>
#include <sstream>

piComm pi(Serial1);

void setup() {
  pi.init();
  Serial.begin(152000);  //init Serial
}

int count = 0;

int lspeed, rspeed;

void parseMe(std::string& data) {
  using namespace std;
  char ch;
  stringstream ss(data);

  if (ss.peek() == '^')
  {
    ss >> ch;

    if (ss.peek() == 'L')
    {
      ss >> ch;
      ss >> lspeed;
      Serial.print(lspeed);
    }
    if (ss.peek() == 'R')
    {
      ss >> ch;
      ss >> rspeed;
      
      Serial.println(rspeed);
    }
  }
  else if (ss.peek() == '?')
  {
    stringstream newss;
    newss << "^L" << lspeed << 'R' << rspeed;
    pi.send(newss.str());
  }
}


void loop() {
  //Serial.println(pi.msgWaiting());
  //delay(1000);
  if (pi.msgWaiting()) {
    auto [success, data] = pi.read();

    if (success) {
      Serial.printf("(%d,%s)\n", success, data.c_str());
      parseMe(data);
      //pi.send(data);
    } else {
      Serial.printf("(%d,None)\n", success);
      while (1)
        ;
    }
  }




}