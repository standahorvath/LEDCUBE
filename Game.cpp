/*
  Game.h - Hlavní třída všech her
*/
#include "Game.h"

Game::Game() {
  
}

#ifdef USE_COM
void Game::setCommunication(Communication * com) {
  _com = com;
}
#endif

#ifdef USE_GYRO
void Game::setGyroscope(Gyroscope * gyro) {
  _gyro = gyro;
}
#endif

#ifdef USE_MATRIX
void Game::setMatrix(Matrix * matrix) {
  _matrix = matrix;
}
#endif

void Game::init(){
}
