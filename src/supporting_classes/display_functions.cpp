#include "display_functions.h"

DisplayFunctions::DisplayFunctions()
  : u8g2(U8G2_R0, /* clock=*/12, /* data=*/14, /* reset=*/U8X8_PIN_NONE) {
}

void DisplayFunctions::init() {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14B_tr);
}

void DisplayFunctions::displayConnectingScreen() {
  u8g2.drawStr(0, 10, "WiFi ...");
  u8g2.sendBuffer();
}

void DisplayFunctions::displayMainScreen(String time, float tempOut, float tempIn) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_12x6LED_mn);

  String time_str = time;
  u8g2.drawStr(0, 12, time_str.c_str());

  u8g2.setFont(u8g2_font_ncenB14_tf);
  char buffer[20];
  sprintf(buffer, "%.1f", tempOut);
  String temp_out_msg = "=> " + String(buffer) + " ^C";
  u8g2.drawStr(0, 35, temp_out_msg.c_str());

  sprintf(buffer, "%.1f", tempIn);
  String temp_in_msg = "<= " + String(buffer) + " ^C";
  u8g2.drawStr(0, 55, temp_in_msg.c_str());

  u8g2.sendBuffer();
}