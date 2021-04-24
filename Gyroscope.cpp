 /*
  Gyroscope.h - Knihovna pro práci s gyroskopem a akcelerátorem MPU-6050
*/
#include "Gyroscope.h"

Gyroscope::Gyroscope() {
  _GyAcX=0;
  _GyAcY=0;
  _GyAcZ=0;
  _Tmp=0;
  _GyX=0;
  _GyY=0;
  _GyZ=0;
}

/* Inicializační funkce */
void Gyroscope::init(){
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

/* Funkce vrací velikost rychlosti náklonu */
int16_t Gyroscope::getGyAcX(){
  return _GyAcX;
}

/* Funkce vrací velikost rychlosti náklonu */
int16_t Gyroscope::getGyAcY(){
  return _GyAcY;
}

/* Funkce vrací velikost rychlosti náklonu */
int16_t Gyroscope::getGyAcZ(){
  return _GyAcZ;
}

/* Funkce vrací naklonění Gyroskopu ve stupních */
float Gyroscope::getRotationDegreesX(){
  return (_GyX/(float)GYRO_MAX_RAW_VALUE)*180;
}

/* Funkce vrací naklonění Gyroskopu ve stupních */
float Gyroscope::getRotationDegreesY(){
  return (_GyY/(float)GYRO_MAX_RAW_VALUE)*180;
}

/* Funkce vrací naklonění Gyroskopu ve stupních */
float Gyroscope::getRotationDegreesZ(){
  return (_GyZ/(float)GYRO_MAX_RAW_VALUE)*180;
}

/* Funkce vrací aktuální teplotu ve stupních celsia */
int16_t Gyroscope::getTmp(){
  return _Tmp;
}

/* Funkce vrací úhel v raw hodnotě */
int16_t Gyroscope::getGyX(){
  return _GyX;
}

/* Funkce vrací úhel v raw hodnotě */
int16_t Gyroscope::getGyY(){
  return _GyY;
}

/* Funkce vrací úhel v raw hodnotě */
int16_t Gyroscope::getGyZ(){
  return _GyZ;
}


/* Cyklická funkce pro časování čtení hodnot */
void Gyroscope::handleFetchValues(){
    long t_micros = micros();
  if(t_micros - _lastSyncTime > GYRO_FETCH_REFRESH_IN_MICROS || t_micros < _lastSyncTime) {
    _lastSyncTime = t_micros;
    fetchValues();
  }
}

/* Cyklická funkce pro čtení hodnot */
void Gyroscope::fetchValues(){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR,14,true);  // request a total of 14 registers
  
  _GyX=Wire.read()<<8|Wire.read();     // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  _GyY=Wire.read()<<8|Wire.read();     // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  _GyZ=Wire.read()<<8|Wire.read();     // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  _Tmp=Wire.read()<<8|Wire.read();     // 0x41 (TEMP_OUT_H)   & 0x42 (TEMP_OUT_L)
  _GyAcX=Wire.read()<<8|Wire.read();     // 0x43 (GYRO_XOUT_H)  & 0x44 (GYRO_XOUT_L)
  _GyAcY=Wire.read()<<8|Wire.read();     // 0x45 (GYRO_YOUT_H)  & 0x46 (GYRO_YOUT_L)
  _GyAcZ=Wire.read()<<8|Wire.read();     // 0x47 (GYRO_ZOUT_H)  & 0x48 (GYRO_ZOUT_L)
}
