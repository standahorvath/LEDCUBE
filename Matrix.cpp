/*
  Matrix.h - Knihovna pro práci s LED maticí
*/
#include "Matrix.h"

Matrix::Matrix() {
  _lastSyncTime = micros();
}


/* Inicializační funkce */
void Matrix::init(const uint8_t PIN){
  _driver = new Adafruit_NeoPixel(MATRIX_WIDTH * MATRIX_HEIGHT, PIN, NEO_GRB + NEO_KHZ800);
  _driver->begin();
  displayClear();
  _driver->show();
}

uint8_t Matrix::getWidth() {
  return MATRIX_WIDTH;
}

uint8_t Matrix::getHeight() {
  return MATRIX_HEIGHT;
}

/* Nastavení jasu v hodnotách 0 - 255 */
void Matrix::setBrightness(uint8_t brightness) {
  _brightness = brightness;
}

uint8_t * Matrix::getPixelData(uint8_t x, uint8_t y) {
  return _data[x][y];
}

/* Metoda naplní jeden pixel barvou */
void Matrix::displaySetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b){
  if(x < MATRIX_WIDTH && y < MATRIX_HEIGHT) {
      _data[x][y][0] = r;
      _data[x][y][1] = g;
      _data[x][y][2] = b;
  }
}

/* Metoda naplní data jednou jedinou barvou */
void Matrix::displayFill(uint8_t r, uint8_t g, uint8_t b){
  uint8_t i, j;
  for(i = 0; i <MATRIX_WIDTH; i++) {
    for(j = 0; j <MATRIX_HEIGHT; j++) {
      _data[i][j][0] = r;
      _data[i][j][1] = g;
      _data[i][j][2] = b;
    }
  }
}

/* Metoda vyčistí data a připraví je tak pro nový frame */
void Matrix::displayClear(){
  uint8_t i, j;
  for(i = 0; i <MATRIX_WIDTH; i++) {
    for(j = 0; j <MATRIX_HEIGHT; j++) {
      _data[i][j][0] = 0;
      _data[i][j][1] = 0;
      _data[i][j][2] = 0;
    }
  }
}

/* Metoda která refreshne display při frekvenci 30hz */
void Matrix::handleSync(){
  long t_micros = micros();
  if(t_micros - _lastSyncTime > MATRIX_REFRESH_TIME_IN_MICROS || t_micros < _lastSyncTime) {
    _lastSyncTime = t_micros;
    displaySync();
  }
}

/* Metoda pro přenos dat do LED Matice */
void Matrix::displaySync(){
  uint8_t i, j;
  float _tb = _brightness/(float)255;
  for(i = 0; i <MATRIX_HEIGHT; i++) {
    for(j = 0; j <MATRIX_WIDTH; j++) {
      _driver->setPixelColor((i*MATRIX_WIDTH)+j, _data[j][i][0]*_tb, _data[j][i][1]*_tb, _data[j][i][2]*_tb);
    }
  }
  _driver->show();
}
