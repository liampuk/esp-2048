#pragma once
#include <Adafruit_SSD1306.h>

// Direction constants
#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

extern int highscores[10];
extern int grid[4][4];
extern bool gameOver;

void addRandom();
void checkGameOver();
void shiftGrid(int dir);
void resetGame(Adafruit_SSD1306 &oled);