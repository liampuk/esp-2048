#include "2048/game.h"
#include "2048/render.h"
#include "buttons.h"
#include "2048/2048.h"
#include "menu/menu.h"
#include "relay.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

enum Mode
{
    M_MENU,
    M_2048,
};

Mode mode = M_2048;

void setup()
{
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
        for (;;)
            ; // loop forever
    }

    Serial.begin(9600);

    pinMode(wButton.pin, INPUT_PULLUP);
    pinMode(aButton.pin, INPUT_PULLUP);
    pinMode(sButton.pin, INPUT_PULLUP);
    pinMode(dButton.pin, INPUT_PULLUP);
    pinMode(menuButton.pin, INPUT_PULLUP);
    pinMode(restartButton.pin, INPUT_PULLUP);

    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Relay off
}

Mode prev_mode = M_MENU;

void loop()
{
    if (read_button(menuButton))
    {
        setClick();
        Serial.println("MENU");
        Mode temp = mode;
        mode = prev_mode;
        prev_mode = temp;
        oled.clearDisplay();
        oled.display();
        if (mode == M_2048)
        {
            resume_2048(oled);
        }
    }
    else if (mode == M_2048)
    {
        loop_2048(oled);
    }
    else if (mode == M_MENU)
    {
        loop_menu(oled);
    }
    playClick();
}
