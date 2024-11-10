#include <Arduino.h>

#include "supporting_classes/time_functions.h"
#include "supporting_classes/temperature_functions.h"
#include "supporting_classes/display_functions.h"
#include "supporting_classes/firebase.h"

#include "env.h"

// Data wire is plugged into port D2 on the ESP8266
#define ONE_WIRE_BUS D2

#define DSIPLAY_TIME_DELAY 1000 // 1 second
#define SEND_DATA_TIME_DELAY 30 * 1000 // 30 seconds


TimeFunctions timeFunctions;
TemperatureFunctions temperatureFunctions(ONE_WIRE_BUS);
DisplayFunctions displayFunctions;
FirebaseFunctions firebaseFunctions;

unsigned long displayTimerTime = 0;
unsigned long sendDataTimerTime = 0;

void setup()
{
  Serial.begin(115200);

  displayFunctions.init();

  WiFi.begin(WIFI_NAME, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    displayFunctions.displayConnectingScreen();
  }

  timeFunctions.init();
  temperatureFunctions.init();
  firebaseFunctions.init();
}

void loop()
{
  unsigned long currentTime = millis();

  if ( currentTime - displayTimerTime >= DSIPLAY_TIME_DELAY ) {
    float *temps = temperatureFunctions.getTemperatures();
    String time = timeFunctions.getFormattedTime();
    displayFunctions.displayMainScreen(time, temps[0], temps[1]);

    displayTimerTime = currentTime;
  }
  
  if ( currentTime - sendDataTimerTime >= SEND_DATA_TIME_DELAY ) {
    sendDataTimerTime = currentTime;
    int timestamp = timeFunctions.getEpochTime();
    float *temps = temperatureFunctions.getTemperatures();
    firebaseFunctions.sendData(temps[0], temps[1], timestamp);
  }

  firebaseFunctions.authHandler();
}