 /*
  Matrix.h - Knihovna pro práci s LED maticí
*/
#ifndef MATRIX_h
#define MATRIX_h
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 6
#define MATRIX_REFRESH_TIME_IN_MICROS 33000
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class Matrix
{
  public:
    Matrix();
    void init(const uint8_t);
    void displayClear();
    void handleSync();
    void displayFill(uint8_t r, uint8_t g, uint8_t b);
    void displaySetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
    uint8_t getWidth();
    uint8_t getHeight();
    uint8_t * getPixelData(uint8_t, uint8_t);
    void setBrightness(uint8_t);
  private:
    Adafruit_NeoPixel * _driver;
    uint8_t _data[MATRIX_WIDTH][MATRIX_HEIGHT][3];
    uint8_t _brightness = 255;
    void displaySync();
    long _lastSyncTime;
};

#endif
