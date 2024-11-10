#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H
#include <U8g2lib.h>

class DisplayFunctions {
  private:
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;
  public:
    DisplayFunctions();
    void init();
    void displayConnectingScreen();
    void displayMainScreen(String time, float tempOut, float tempIn);
};

#endif