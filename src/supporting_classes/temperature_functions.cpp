#include "temperature_functions.h"

TemperatureFunctions::TemperatureFunctions(int dataPin) : oneWire(dataPin), sensors(&oneWire) {

}

void TemperatureFunctions::init() {
   sensors.begin();
}


float* TemperatureFunctions::getTemperatures() {
  float *result = new float[2];
  sensors.requestTemperatures(); 
  result[0] = sensors.getTempCByIndex(0);
  result[1] = sensors.getTempCByIndex(1);
  return result;
}