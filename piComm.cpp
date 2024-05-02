#include <Arduino.h>
#include "piComm.h"


int checksum(const std::string& sentence) {
  uint8_t calc_cksum = 0;
  for (char c : sentence)
    calc_cksum ^= c;

  return calc_cksum;
}

piComm::piComm(SerialUART& serial): ser(serial)
{// do nothing
}

void piComm::init()
{
  ser.setTX(0);
  ser.setRX(1);
  ser.begin(9600);
}

void piComm::send(std::string value)
{  // not a reference because we are gonna modify it... so might as well copy
  auto cs = checksum(value);
  value += '*' + std::to_string(cs) + '\n';
  ser.print(value.c_str());
}

bool piComm::msgWaiting()
{
  return ser.available() > 0;
}

std::pair<bool, std::string> piComm::read()
{
  bool success = true;
  constexpr int bufsize = 200;
  char buf[bufsize + 3];
  size_t numbytes = ser.readBytesUntil('\n', buf, bufsize);
  buf[numbytes] = '\0';
  std::string value(buf);

  if (value.back() == '\n') {
    value.resize(value.size() - 1);
  }

  constexpr char delimiter = '*';
  auto pos = value.find(delimiter);
  std::string sentence = value.substr(0, pos);
  auto crc = std::stoi(value.substr(pos + 1));

  success = (crc == checksum(sentence));

  auto ret = std::make_pair(success, sentence);

  return ret;
}
