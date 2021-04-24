 /*
  Game.h - Hlavní třída všech her
*/
#ifndef GAME_h
#define GAME_h
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

class Game
{
  public:
    Game();
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

  virtual void handleGame() = 0;
  
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
