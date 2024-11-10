#include "time_functions.h"

TimeFunctions::TimeFunctions() : timeClient(new NTPClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds)) {

}

void TimeFunctions::init() {
  timeClient->begin();
}

String TimeFunctions::getFormattedTime() {
  timeClient->update();
  return timeClient->getFormattedTime();
}

int TimeFunctions::getEpochTime() {
  return timeClient->getEpochTime();
}