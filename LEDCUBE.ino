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

#ifdef USE_DEBUG
#include "Debugger.h"
#endif

#include "GameDemonstration.h"

#ifdef USE_COM
Communication * com;
#endif

#ifdef USE_GYRO
Gyroscope     * gyro;
#endif

#ifdef USE_MATRIX
Matrix        * matrix;
#endif

#ifdef USE_DEBUG
Debugger         * debug;
#endif

GameDemonstration * game;

void setup() {

  game = new GameDemonstration();


#ifdef USE_DEBUG
  debug   = new Debugger();
  debug->init();
#endif

#ifdef USE_COM
  com     = new Communication(115200);
  com->setTopCom(    TOP_COM_RX,     TOP_COM_TX);      // INIT TOP COMMUNICATION
  com->setRightCom(  RIGHT_COM_RX,   RIGHT_COM_TX);    // INIT RIGHT COMMUNICATION
  com->setBottomCom( BOTTOM_COM_RX,  BOTTOM_COM_TX);   // INIT BOTTOM COMMUNICATION
  com->setLeftCom(   LEFT_COM_RX,    LEFT_COM_TX);     // INIT LEFT COMMUNICATION

  game->setCommunication(com);
  
  #ifdef USE_DEBUG
  debug->setCommunication(com);
  #endif
  
#endif

#ifdef USE_GYRO
  gyro    = new Gyroscope();
  gyro->init();                                         // INIT GYROSCOPE

  game->setGyroscope(gyro);       
  
  #ifdef USE_DEBUG
  debug->setGyroscope(gyro);    
  #endif
                              
#endif

#ifdef USE_MATRIX
  matrix  = new Matrix();
  matrix->init(      MATRIX_PIN);                      // INIT LED MATRIX
  game->setMatrix(matrix);        
  
  #ifdef USE_DEBUG
  debug->setMatrix(matrix);     
  #endif
  
#endif

  game->init();
}

void loop() {

  #ifdef USE_COM
    com->handleCommunication();
  #endif
  
  #ifdef USE_GYRO
    gyro->handleFetchValues();                                     
  #endif

  #ifdef USE_MATRIX
    matrix->handleSync();  
  #endif

  #ifdef USE_DEBUG
    debug->handleDebug();  
  #endif
  
  game->handleGame();

}
