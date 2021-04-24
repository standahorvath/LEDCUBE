 /*
  Gyroscope.h - Knihovna pro práci s gyroskopem a akcelerátorem MPU-6050 
*/
#ifndef GYROSCOPE_h
#define GYROSCOPE_h
#define MPU_ADDR 0x68
#define GYRO_FETCH_REFRESH_IN_MICROS 66000
#define GYRO_MAX_RAW_VALUE 16500
#include "Arduino.h"
#include <Wire.h>

class Gyroscope
{
  public:
    Gyroscope();
    void init();
    int16_t getGyAcX();
    int16_t getGyAcY();
    int16_t getGyAcZ();
    int16_t getTmp();
    int16_t getGyX();
    int16_t getGyY();
    int16_t getGyZ();
    void handleFetchValues();
    float getRotationDegreesX();
    float getRotationDegreesY();
    float getRotationDegreesZ();
  private:
    int16_t _GyAcX;
    int16_t _GyAcY;
    int16_t _GyAcZ;
    int16_t _Tmp;
    int16_t _GyX;
    int16_t _GyY;
    int16_t _GyZ;
    void fetchValues();
    long _lastSyncTime;
};

#endif
