 /*
  Communication.h - Funkce pro komunikaci s ostatními moduly zkrze serial porty.
*/
#ifndef COMM_h
#define COMM_h
#include <SoftwareSerial.h>
#include "Arduino.h"
#define default_change_time 1000
#define COM_HANDLE_PERIOD_IN_MICROS 1000
#define COM_BUFFER_SIZE 16

class Communication
{
  public:
    Communication(long);
    void setTopCom(uint8_t, uint8_t);
    void setRightCom(uint8_t, uint8_t);
    void setBottomCom(uint8_t, uint8_t);
    void setLeftCom(uint8_t, uint8_t);
    void handleCommunication();
  private:
  void pushDataBuffer(uint8_t buffer, uint8_t value);
  void clearBuffer(uint8_t * com_buffer);
  SoftwareSerial * topCom;
  SoftwareSerial * rightCom;
  SoftwareSerial * bottomCom;
  SoftwareSerial * leftCom;
  long _baudrate;
  int _serial_change_timeout;
  uint8_t _active_serial;  
  long _lastSyncTime;
  uint8_t _topComBuffer[COM_BUFFER_SIZE];
  uint8_t _rightComBuffer[COM_BUFFER_SIZE];
  uint8_t _bottomComBuffer[COM_BUFFER_SIZE];
  uint8_t _leftComBuffer[COM_BUFFER_SIZE];
  uint8_t _topComBufferIndex;
  uint8_t _rightComBufferIndex;
  uint8_t _bottomComBufferIndex;
  uint8_t _leftComBufferIndex;
};

#endif
