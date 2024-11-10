#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H
#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeFunctions {
  private:
    long utcOffsetInSeconds = 3600 * 2;
    WiFiUDP ntpUDP;
    NTPClient *timeClient;
  public:
    TimeFunctions();
    void init();
    String getFormattedTime();
    int getEpochTime();
};

#endif