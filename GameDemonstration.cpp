/*
  GameDemonstration.h - Demonstrace jednoduché hry
*/
#include "GameDemonstration.h"

GameDemonstration::GameDemonstration() {
  
}


void GameDemonstration::init(){
  _matrix->setBrightness(255);
}


void GameDemonstration::handleGame() {
  long t_micros = micros();
  if(t_micros - _lastSyncTime > GAME_PERIOD_IN_MICROS || t_micros < _lastSyncTime) {
    _lastSyncTime = t_micros;

  _matrix->displayClear();
  _matrix->displaySetPixel((_gyro->getGyY()/1670)+4, (_gyro->getGyX()/1670)+2, 255, 255, 255);
  _matrix->displaySetPixel((_gyro->getGyY()/1670)+3, (_gyro->getGyX()/1670)+2, 255, 255, 255);
  _matrix->displaySetPixel((_gyro->getGyY()/1670)+4, (_gyro->getGyX()/1670)+3, 255, 255, 255);
  _matrix->displaySetPixel((_gyro->getGyY()/1670)+3, (_gyro->getGyX()/1670)+3, 255, 255, 255);
  }
  _matrix->displayFill(255,255,255);
}
