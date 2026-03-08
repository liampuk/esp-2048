#include "2048.h"
#include "game.h"
#include "render.h"
#include "buttons.h"
#include "buzzer.h"
#include <Adafruit_SSD1306.h>

bool setup_completed = false;

void setup_2048(Adafruit_SSD1306 &oled)
{
    oled.clearDisplay();
    addRandom();
    renderGrid(grid, oled);
    oled.display();
    setup_completed = true;
}

void resume_2048(Adafruit_SSD1306 &oled)
{
    if (!setup_completed)
    {
        setup_2048(oled);
    }
    renderGrid(grid, oled);
    oled.display();
}

void loop_2048(Adafruit_SSD1306 &oled)
{
    if (!setup_completed)
    {
        setup_2048(oled);
    }
    if (read_button(restartButton))
    {
        setClick();
        Serial.println("RESTART");
        resetGame(oled);
    }
    if (gameOver)
    {
        int highscores_len = sizeof(highscores) / sizeof(highscores[0]);
        renderGameOver(highscores, highscores_len, grid, oled);
    }
    else
    {

        if (read_button(wButton))
        {
            Serial.println("W");
            shiftGrid(DIR_UP);
            renderGrid(grid, oled);
            oled.display();
        }
        if (read_button(sButton))
        {
            Serial.println("S");
            shiftGrid(DIR_DOWN);
            renderGrid(grid, oled);
            oled.display();
        }
        if (read_button(aButton))
        {
            Serial.println("A");
            shiftGrid(DIR_LEFT);
            renderGrid(grid, oled);
            oled.display();
        }
        if (read_button(dButton))
        {
            Serial.println("D");
            shiftGrid(DIR_RIGHT);
            renderGrid(grid, oled);
            oled.display();
        }
    }
}
