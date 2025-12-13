#include "menu.h"
#include <Adafruit_SSD1306.h>

void loop_menu(Adafruit_SSD1306 &oled)
{
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println("Menu");
    oled.println("q: back");
    oled.println("a: 2048");
    oled.println("s: snake");
    oled.println("d: tetris");
    oled.display();
}