 /*
  Gyroscope.h - Knihovna pro práci s gyroskopem a akcelerátorem MPU-6050 
*/
#ifndef DEBUGGER_h
#define DEBUGGER_h
#define DEBUG_LOG_IN_MICROS 100000
#define SERIAL_BOUDRATE 115200
#include "Arduino.h"

#include "Config.h"

#ifdef USE_COM
#include "Communication.h"
#endif

#ifdef USE_GYRO
#include "Gyroscope.h"
#endif

#ifdef USE_MATRIX
#include "Matrix.h"
#endif


class Debugger
{
  public:
    Debugger();
    void init();
      
  #ifdef USE_COM
    void setCommunication(Communication * c);
  #endif
  #ifdef USE_GYRO
    void setGyroscope(Gyroscope * g);
  #endif
  #ifdef USE_MATRIX
    void setMatrix(Matrix * m);
  #endif


  void handleDebug();
  void debugModules();
  
  private:
  long _lastSyncTime;
  
  protected:
  #ifdef USE_COM
  Communication * _com;
  #endif
  #ifdef USE_GYRO
  Gyroscope     * _gyro;
  #endif
  #ifdef USE_MATRIX
  Matrix        * _matrix;
  #endif
  
};

#endif
