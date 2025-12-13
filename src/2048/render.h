#pragma once
#include <cstdint>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void drawChar3x5(int16_t x, int16_t y, char c, uint16_t color, Adafruit_SSD1306 &oled);
void drawString3x5(int16_t x, int16_t y, const char *str, uint16_t color, Adafruit_SSD1306 &oled);
void render_bg(int x, int y, int num, Adafruit_SSD1306 &oled);
void renderGrid(int grid[4][4], Adafruit_SSD1306 &oled);
void renderGameOverLine(int y, int colour, int num, std::string sum_str, Adafruit_SSD1306 &oled);
void renderGameOver(int highscores[], int highscores_len, int (*grid)[4], Adafruit_SSD1306 &oled);