
#include <string>
#include <utility>

#ifndef __piComm_H__
#define __piComm_H__
/**
 * \brief wraps a Serial object so data transmission is crc checksummed.
 */
class piComm {
  SerialUART& ser;  // it's ok to do this ONLY because all serial objects are global... otherwise fire me

public:
  /**
   * \brief Constructor for piComm
   * \param serial the Serial object (usually Serial1 or Serial2)
   */
  piComm(SerialUART& serial);

  /**
   * \brief initializes the serial port 
   */
  void init();

  /**
   * \brief sends a string value
   * \param value the string value to send (no \n in string please)
   */
  void send(std::string value);

  /**
   * \brief is there any data in the Serial queue
   * \return true if there is data
   */
  bool msgWaiting();

  /**
   * \brief reads back data from serial port
   * \return a <bool,string> pair - if the bool is true it means transmission and crc as successful and the string is valid
   *                                otherwise ignore the string
   */
  std::pair<bool, std::string> read();
};
#endif