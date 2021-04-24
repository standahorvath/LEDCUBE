 /*
  Gyroscope.h - Knihovna pro práci s gyroskopem a akcelerátorem MPU-6050
*/
#include "Debugger.h"

Debugger::Debugger() {
}

/* Inicializační funkce */
void Debugger::init(){
  Serial.begin(SERIAL_BOUDRATE);  
}

#ifdef USE_COM
void Debugger::setCommunication(Communication * com) {
  _com = com;
}
#endif

#ifdef USE_GYRO
void Debugger::setGyroscope(Gyroscope * gyro) {
  _gyro = gyro;
}
#endif

#ifdef USE_MATRIX
void Debugger::setMatrix(Matrix * matrix) {
  _matrix = matrix;
}
#endif


/* Cyklická funkce pro spuštění debugu */
void Debugger::handleDebug(){
    long t_micros = micros();
  if(t_micros - _lastSyncTime > DEBUG_LOG_IN_MICROS || t_micros < _lastSyncTime) {
    _lastSyncTime = t_micros;
    debugModules();
  }
}

/* Debug hodnot */
void Debugger::debugModules(){

#ifdef USE_GYRO
  Serial.print("GYRO;");
  Serial.print("GyAcX=");
  Serial.print(_gyro->getGyAcX());
  Serial.print(";");
  
  Serial.print("GyAcY=");
  Serial.print(_gyro->getGyAcY());
  Serial.print(";");
  
  Serial.print("GyAcZ=");
  Serial.print(_gyro->getGyAcZ());
  Serial.print(";");

  Serial.print("Tmp=");
  Serial.print(_gyro->getTmp());
  Serial.print(";");
  
  Serial.print("GyX=");
  Serial.print(_gyro->getGyX());
  Serial.print(";");
    
  Serial.print("GyY=");
  Serial.print(_gyro->getGyY());
  Serial.print(";");
  
  Serial.print("GyZ=");
  Serial.print(_gyro->getGyZ());
  Serial.print(";");
  Serial.print("\n");
#endif

#ifdef USE_MATRIX
  uint8_t i,j;
  Serial.print("MATRIX;");
  for(i = 0; i<_matrix->getHeight(); i++) {
    for(j = 0; j<_matrix->getWidth(); j++) {
      uint8_t * pixeldata = _matrix->getPixelData(j, i);
      Serial.print(pixeldata[0]);
      Serial.print(",");
      Serial.print(pixeldata[1]);
      Serial.print(",");
      Serial.print(pixeldata[2]);
      Serial.print(";");
    }
  }
  Serial.print("\n");
#endif


}
