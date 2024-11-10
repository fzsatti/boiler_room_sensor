#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H
#include <OneWire.h>
#include <DallasTemperature.h>
#include<Arduino.h>
#include<Wire.h>
#include <ESP8266WiFi.h>

class TemperatureFunctions {
  private:
    OneWire oneWire;
    // Pass our oneWire reference to Dallas Temperature.
    DallasTemperature sensors;
  public:
    TemperatureFunctions(int dataPin);
    void init();
    float* getTemperatures();
};

#endif