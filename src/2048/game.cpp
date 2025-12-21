#include <cstdlib>
#include <Adafruit_SSD1306.h>
#include "game.h"
#include "render.h"
#include "relay.h"

int highscores[10] = {5010, 5009, 5008, 5007, 5006, 5005, 5004, 5003, 5002, 5001};

// start
int grid[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

// almost gameover high
// int grid[4][4] = {
//     {8, 32, 8, 512},
//     {512, 8, 1024, 8},
//     {8, 2048, 8, 64},
//     {16, 8, 0, 0}};

// almost gameover low
// int grid[4][4] = {
//     {2, 4, 2, 4},
//     {16, 32, 16, 32},
//     {8, 4, 8, 64},
//     {16, 32, 0, 0}};

// all number sizes
// int grid[4][4] = {
//     {2, 4, 8, 16},
//     {32, 64, 128, 256},
//     {512, 1024, 2048, 0},
//     {0, 0, 0, 0}};

// all numbers
// int grid[4][4] = {
//     {2, 4, 8, 16},
//     {32, 64, 128, 256},
//     {512, 1024, 2048, 4096},
//     {8192, 16384, 32768, 65536}};

bool gameOver = false;

// Add random number to grid
void addRandom()
{
    int empty[16][2];
    int emptyCount = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (grid[y][x] == 0)
            {
                empty[emptyCount][0] = x;
                empty[emptyCount][1] = y;
                emptyCount++;
            }
        }
    }
    if (emptyCount > 0)
    {
        int r = rand() % emptyCount;
        int value = (rand() % 10 < 9) ? 2 : 4; // 90% chance of 2, 10% chance of 4
        grid[empty[r][1]][empty[r][0]] = value;
    }
}

void checkGameOver()
{
    // Check for any empty cells
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (grid[y][x] == 0)
            {
                return; // Not game over, there's at least one empty cell
            }
        }
    }

    // Check for possible merges horizontally
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (grid[y][x] == grid[y][x + 1])
            {
                return; // Not game over, there's a possible horizontal merge
            }
        }
    }

    // Check for possible merges vertically
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (grid[y][x] == grid[y + 1][x])
            {
                return; // Not game over, there's a possible vertical merge
            }
        }
    }

    // If no empty cells and no possible merges, it's game over
    gameOver = true;
}

void shiftGrid(int dir)
{
    bool changed = false;
    for (int i = 0; i < 4; i++)
    {
        int lastMerge = (dir == DIR_UP || dir == DIR_LEFT) ? -1 : 4;
        for (int j = (dir == DIR_UP || dir == DIR_LEFT) ? 1 : 2;
             (dir == DIR_UP || dir == DIR_LEFT) ? j < 4 : j >= 0;
             (dir == DIR_UP || dir == DIR_LEFT) ? j++ : j--)
        {
            int *cell, *targetCell;
            int value, targetIdx = j;
            if (dir == DIR_UP || dir == DIR_DOWN)
            {
                cell = &grid[j][i];
                value = grid[j][i];
            }
            else
            {
                cell = &grid[i][j];
                value = grid[i][j];
            }
            if (value == 0)
                continue;
            // Find target
            while ((dir == DIR_UP && targetIdx > 0 && grid[targetIdx - 1][i] == 0) ||
                   (dir == DIR_DOWN && targetIdx < 3 && grid[targetIdx + 1][i] == 0) ||
                   (dir == DIR_LEFT && targetIdx > 0 && grid[i][targetIdx - 1] == 0) ||
                   (dir == DIR_RIGHT && targetIdx < 3 && grid[i][targetIdx + 1] == 0))
            {
                targetIdx += (dir == DIR_UP || dir == DIR_LEFT) ? -1 : 1;
            }
            // Merge
            if ((dir == DIR_UP && targetIdx > 0 && grid[targetIdx - 1][i] == value && lastMerge != targetIdx - 1) ||
                (dir == DIR_DOWN && targetIdx < 3 && grid[targetIdx + 1][i] == value && lastMerge != targetIdx + 1) ||
                (dir == DIR_LEFT && targetIdx > 0 && grid[i][targetIdx - 1] == value && lastMerge != targetIdx - 1) ||
                (dir == DIR_RIGHT && targetIdx < 3 && grid[i][targetIdx + 1] == value && lastMerge != targetIdx + 1))
            {
                if (dir == DIR_UP || dir == DIR_DOWN)
                {
                    grid[(dir == DIR_UP) ? targetIdx - 1 : targetIdx + 1][i] *= 2;
                    grid[j][i] = 0;
                    lastMerge = (dir == DIR_UP) ? targetIdx - 1 : targetIdx + 1;
                }
                else
                {
                    grid[i][(dir == DIR_LEFT) ? targetIdx - 1 : targetIdx + 1] *= 2;
                    grid[i][j] = 0;
                    lastMerge = (dir == DIR_LEFT) ? targetIdx - 1 : targetIdx + 1;
                }
                changed = true;
                // setClick();
            }
            // Move
            else if (targetIdx != j)
            {
                if (dir == DIR_UP || dir == DIR_DOWN)
                {
                    grid[targetIdx][i] = value;
                    grid[j][i] = 0;
                }
                else
                {
                    grid[i][targetIdx] = value;
                    grid[i][j] = 0;
                }
                changed = true;
            }
        }
    }
    if (changed)
    {
        addRandom();
        checkGameOver();
    }
}

void resetGame(Adafruit_SSD1306 &oled)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            grid[y][x] = 0;
        }
    }
    gameOver = false;
    addRandom();
    renderGrid(grid, oled);
    oled.display();
}