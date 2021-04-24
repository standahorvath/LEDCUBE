/*
  Communication.h - Funkce pro komunikaci s ostatními moduly zkrze serial porty.
*/
#include "Arduino.h"
#include "Communication.h"

Communication::Communication(long baudrate) {
  Serial.begin(baudrate);
  _baudrate = baudrate;
  _active_serial = 0;
  _serial_change_timeout = default_change_time;
  
  _topComBufferIndex = 0;
  _rightComBufferIndex = 0;
  _bottomComBufferIndex = 0;
  _leftComBufferIndex = 0;

  clearBuffer(_topComBuffer);
  clearBuffer(_rightComBuffer);
  clearBuffer(_bottomComBuffer);
  clearBuffer(_leftComBuffer);
}




/* Metoda vloží do bufferu další hodnotu - buffer = číslo bufferu 0-3 */
void Communication::pushDataBuffer(uint8_t buffer, uint8_t value) {
  uint8_t * index;
  uint8_t * com_buffer;
  
  switch(buffer) {
    case 0:
      index = &_topComBufferIndex;
      com_buffer = _topComBuffer;
    break;
    case 1:
      index = &_rightComBufferIndex;
      com_buffer = _rightComBuffer;
    break;
    case 2:
      index = &_bottomComBufferIndex;
      com_buffer = _bottomComBuffer;
    break;
    case 3:
      index = &_leftComBufferIndex;
      com_buffer = _leftComBuffer;
    break;
    default:
    return;
  }

  if(*index < COM_BUFFER_SIZE) {
    com_buffer[*index] = value;
    (*index)++;
  } else {
      uint8_t i;
      for(i = 1; i < COM_BUFFER_SIZE; i++) {
        com_buffer[i-1] = com_buffer[i];
      }
      com_buffer[COM_BUFFER_SIZE-1] = value;
  }
  
}


/* Metoda vyprázdní buffer */
void Communication::clearBuffer(uint8_t * com_buffer) {
  uint8_t i;
  for(i = 0; i < COM_BUFFER_SIZE; i++) {
    com_buffer[i] = 0;
  }
}

/* Nastavení pinů horní seriové komunikace */
void Communication::setTopCom(const uint8_t RX,const uint8_t TX)
{
  topCom = new SoftwareSerial(RX, TX);
  topCom->begin(_baudrate);
}

/* Nastavení pinů pravé seriové komunikace */
void Communication::setRightCom(const uint8_t RX,const uint8_t TX)
{
  rightCom = new SoftwareSerial(RX, TX);
  rightCom->begin(_baudrate);
}

/* Nastavení pinů dolní sériové komunikace */
void Communication::setBottomCom(const uint8_t RX,const  uint8_t TX)
{
  bottomCom = new SoftwareSerial(RX, TX);
  bottomCom->begin(_baudrate);
}

/* Nastavení pinů levé seriové komunikace */
void Communication::setLeftCom(const uint8_t RX,const  uint8_t TX)
{
  leftCom = new SoftwareSerial(RX, TX);
  leftCom->begin(_baudrate);
}

void Communication::handleCommunication(){
  long t_micros = micros();
  if(t_micros - _lastSyncTime > COM_HANDLE_PERIOD_IN_MICROS || t_micros < _lastSyncTime) {
    _serial_change_timeout--;
    
    if (_active_serial == 0 && topCom->available() > 0){
      byte reading = topCom->read(); 
      pushDataBuffer(_active_serial, reading);
      _serial_change_timeout = default_change_time;
    } else if (_active_serial == 1 && rightCom->available() > 0){
      byte reading = rightCom->read();
      pushDataBuffer(_active_serial, reading);
      _serial_change_timeout = default_change_time;
    } else if (_active_serial == 2 && bottomCom->available() > 0){
      byte reading = bottomCom->read();
      pushDataBuffer(_active_serial, reading);
      _serial_change_timeout = default_change_time;
    } else if (_active_serial == 3 && leftCom->available() > 0){
      byte reading = leftCom->read();
      pushDataBuffer(_active_serial, reading);
      _serial_change_timeout = default_change_time;
    }
  
    if(_serial_change_timeout != default_change_time && _serial_change_timeout == 0) {
        _active_serial++;
        if(_active_serial>3) {
          _active_serial = 0;
        }
        
        switch(_active_serial) {
          case 0:
          topCom->listen();
          break;
          case 1:
          rightCom->listen();
          break;
          case 2:
          bottomCom->listen();
          break;
          case 3:
          leftCom->listen();
          break;
        }
    }
    
  }
}
