#include "render.h"
#include <Adafruit_SSD1306.h>

const uint8_t font3x5[][5] PROGMEM = {
    {0b111, 0b101, 0b101, 0b101, 0b111}, // '0'
    {0b010, 0b110, 0b010, 0b010, 0b111}, // '1'
    {0b111, 0b001, 0b111, 0b100, 0b111}, // '2'
    {0b111, 0b001, 0b111, 0b001, 0b111}, // '3'
    {0b101, 0b101, 0b111, 0b001, 0b001}, // '4'
    {0b111, 0b100, 0b111, 0b001, 0b111}, // '5'
    {0b111, 0b100, 0b111, 0b101, 0b111}, // '6'
    {0b111, 0b001, 0b010, 0b010, 0b010}, // '7'
    {0b111, 0b101, 0b111, 0b101, 0b111}, // '8'
    {0b111, 0b101, 0b111, 0b001, 0b111}, // '9'
    {0b000, 0b010, 0b000, 0b010, 0b000}, // ':'
    {0b000, 0b010, 0b000, 0b010, 0b010}, // ';'
    {0b000, 0b010, 0b100, 0b010, 0b000}, // '<'
    {0b000, 0b111, 0b000, 0b111, 0b000}, // '='
    {0b000, 0b010, 0b001, 0b010, 0b000}, // '>'
    {0b111, 0b001, 0b010, 0b000, 0b010}, // '?'
    {0b111, 0b101, 0b111, 0b100, 0b111}, // '@'
    {0b111, 0b101, 0b111, 0b101, 0b101}, // 'A'
    {0b110, 0b101, 0b110, 0b101, 0b110}, // 'B'
    {0b111, 0b100, 0b100, 0b100, 0b111}, // 'C'
    {0b110, 0b101, 0b101, 0b101, 0b110}, // 'D'
    {0b111, 0b100, 0b110, 0b100, 0b111}, // 'E'
    {0b111, 0b100, 0b110, 0b100, 0b100}, // 'F'
    {0b111, 0b100, 0b101, 0b101, 0b111}, // 'G'
    {0b101, 0b101, 0b111, 0b101, 0b101}, // 'H'
    {0b111, 0b010, 0b010, 0b010, 0b111}, // 'I'
    {0b001, 0b001, 0b001, 0b101, 0b010}, // 'J'
    {0b100, 0b100, 0b101, 0b110, 0b101}, // 'K'
    {0b100, 0b100, 0b100, 0b100, 0b111}, // 'L'
    {0b101, 0b111, 0b111, 0b101, 0b101}, // 'M'
    {0b101, 0b111, 0b111, 0b111, 0b101}, // 'N'
    {0b111, 0b101, 0b101, 0b101, 0b111}, // 'O'
    {0b111, 0b101, 0b111, 0b100, 0b100}, // 'P'
    {0b010, 0b101, 0b101, 0b111, 0b011}, // 'Q'
    {0b111, 0b101, 0b110, 0b101, 0b101}, // 'R'
    {0b111, 0b100, 0b111, 0b001, 0b111}, // 'S'
    {0b111, 0b010, 0b010, 0b010, 0b010}, // 'T'
    {0b101, 0b101, 0b101, 0b101, 0b011}, // 'U'
    {0b101, 0b101, 0b101, 0b010, 0b010}, // 'V'
    {0b101, 0b101, 0b111, 0b111, 0b101}, // 'W'
    {0b101, 0b101, 0b010, 0b101, 0b101}, // 'X'
    {0b101, 0b101, 0b010, 0b010, 0b010}, // 'Y'
    {0b111, 0b001, 0b010, 0b100, 0b111}, // 'Z'
    {0b010, 0b010, 0b010, 0b000, 0b010}  // '! ([)'
};

void drawChar3x5(int16_t x, int16_t y, char c, uint16_t color, Adafruit_SSD1306 &oled)
{
    if (c == '!')
        c = '['; // map ! to [ for char map
    if (c < '0' || c > '[')
    {
        return;
    }
    const uint8_t *bitmap = font3x5[c - '0'];
    for (int row = 0; row < 5; row++)
    {
        uint8_t bits = pgm_read_byte(&bitmap[row]);
        for (int col = 0; col < 3; col++)
        {
            if (bits & (1 << (2 - col)))
            {
                oled.drawPixel(x + col, y + row, color);
            }
        }
    }
}

void drawString3x5(int16_t x, int16_t y, const char *str, uint16_t color, Adafruit_SSD1306 &oled)
{
    while (*str)
    {
        drawChar3x5(x, y, *str++, color, oled);
        x += 4; // 3 pixels wide + 1 pixel space
    }
}

void render_bg(int x, int y, int num, Adafruit_SSD1306 &oled)
{
    oled.fillRect(x + 1, y + 1, 17, 14, SSD1306_BLACK);
    for (int i = 0; i < 17; i += 1)
    {
        for (int j = 0; j < 14; j += 1)
        {
            bool shouldDraw = true;

            switch (num)
            {
            case 1024:
                shouldDraw = !((j == 1 || j == 12) && (i - 2) % 6 == 0);
                break;
            case 512:
                shouldDraw = !(j % 2 == 0 && (i + j) % 4 == 0);
                break;
            case 256:
                shouldDraw = (i + j - 1) % 3 != 0;
                break;
            case 128:
                shouldDraw = (i + j - 1) % 2 != 0;
                break;
            case 64:
                shouldDraw = (i + j - 1) % 3 == 0;
                break;
            case 32:
                shouldDraw = (i + j - 1) % 4 == 0;
                break;
            case 16:
                shouldDraw = (i + j - 1) % 5 == 0;
                break;
            case 8:
                // shouldDraw = j % 2 == 0 && (i + j) % 4 == 0;
                shouldDraw = (i + j - 4) % 7 == 0;
                break;
            case 4:
            case 2:
            case 0:
                shouldDraw = false;
                break;
            }

            if (shouldDraw)
            {
                oled.drawPixel(x + 1 + i, y + 1 + j, SSD1306_WHITE);
            }
            // if (!(j % 2 == 0 && (i + j) % 4 == 0)) // 1024
            // if ((i + j) % 5 != 0) // 512
            // if ((i + j) % 4 != 0) // 256
            // if ((i + j) % 3 != 0) // 128
            // if ((i + j) % 2 == 0) // 64
            // if ((i + j) % 3 == 0) // 32
            // if ((i + j) % 4 == 0) // 16
            // if ((i + j) % 5 == 0) // 8
            // if (j % 2 == 0 && (i + j) % 4 == 0) // 4
            // {
            //     oled.drawPixel(x + 1 + i, y + 1 + j, SSD1306_WHITE);
            // }
        }
    }
}

int char_offset_y = 6;

void renderGrid(int grid[4][4], Adafruit_SSD1306 &oled)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            int top_x = 27 + x * 18;
            int top_y = 2 + y * 15;

            render_bg(top_x, top_y, grid[y][x], oled);
            oled.drawRect(top_x, top_y, 19, 16, SSD1306_WHITE);
            if (grid[y][x] != 0)
            {
                if (grid[y][x] < 10)
                {
                    oled.fillRect(top_x + 6, top_y + char_offset_y - 2, 7, 9, SSD1306_BLACK);
                    drawChar3x5(top_x + 8, top_y + char_offset_y, '0' + grid[y][x], SSD1306_WHITE, oled);
                }
                else if (grid[y][x] < 100)
                {
                    oled.fillRect(top_x + 4, top_y + char_offset_y - 2, 11, 9, SSD1306_BLACK);
                    if (grid[y][x] >= 32)
                    {
                        oled.drawRect(top_x + 4, top_y + char_offset_y - 2, 11, 9, SSD1306_WHITE);
                    }

                    drawChar3x5(top_x + 6, top_y + char_offset_y, '0' + grid[y][x] / 10, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 10, top_y + char_offset_y, '0' + grid[y][x] % 10, SSD1306_WHITE, oled);
                }
                else if (grid[y][x] < 1000)
                {
                    oled.fillRect(top_x + 2, top_y + char_offset_y - 2, 15, 9, SSD1306_BLACK);
                    oled.drawRect(top_x + 2, top_y + char_offset_y - 2, 15, 9, SSD1306_WHITE);
                    drawChar3x5(top_x + 4, top_y + char_offset_y, '0' + grid[y][x] / 100, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 8, top_y + char_offset_y, '0' + (grid[y][x] / 10) % 10, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 12, top_y + char_offset_y, '0' + grid[y][x] % 10, SSD1306_WHITE, oled);
                }
                else if (grid[y][x] <= 10000)
                {
                    oled.fillRect(top_x + 1, top_y + char_offset_y - 1, 17, 7, SSD1306_BLACK);
                    drawChar3x5(top_x + 2, top_y + char_offset_y, '0' + grid[y][x] / 1000, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 6, top_y + char_offset_y, '0' + (grid[y][x] / 100) % 10, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 10, top_y + char_offset_y, '0' + (grid[y][x] / 10) % 10, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 14, top_y + char_offset_y, '0' + grid[y][x] % 10, SSD1306_WHITE, oled);
                }
                else
                {
                    oled.fillRect(top_x + 2, top_y + char_offset_y - 2, 15, 9, SSD1306_BLACK);
                    oled.drawRect(top_x + 2, top_y + char_offset_y - 2, 15, 9, SSD1306_WHITE);
                    drawChar3x5(top_x + 4, top_y + char_offset_y, '0' + grid[y][x] / 10000, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 8, top_y + char_offset_y, '0' + (grid[y][x] / 1000) % 10, SSD1306_WHITE, oled);
                    drawChar3x5(top_x + 12, top_y + char_offset_y, 'K', SSD1306_WHITE, oled);
                }
            }
        }
    }
}

void renderGameOverLine(int y, int colour, int num, std::string sum_str, Adafruit_SSD1306 &oled)
{
    drawString3x5(44, y, std::to_string(num).c_str(), colour, oled);
    drawString3x5(90 - (sum_str.length() * 4), y, sum_str.c_str(), colour, oled);
}

unsigned long previousMillis = 0;
const long frameInterval = 500; // ms between animation frames
bool gameOverMode = true;

void renderGameOver(int highscores[], int highscores_len, int (*grid)[4], Adafruit_SSD1306 &oled)
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= frameInterval)
    {
        previousMillis = currentMillis;
        gameOverMode = !gameOverMode;
    }

    oled.drawRect(33, 7, 61, 49, SSD1306_WHITE);
    oled.fillRect(34, 8, 59, 47, SSD1306_BLACK);
    oled.drawLine(33, 19, 92, 19, SSD1306_WHITE);

    drawString3x5(44, 11, "HIGH", SSD1306_WHITE, oled);
    drawString3x5(63, 11, "SCORE", SSD1306_WHITE, oled);

    int line_top = 23;
    int line_height = 8;

    // drawChar3x5(38, 23, '1', SSD1306_WHITE);
    // drawChar3x5(38, 31, '2', SSD1306_WHITE);
    // drawChar3x5(38, 39, '3', SSD1306_WHITE);
    // drawChar3x5(38, 47, '4', SSD1306_WHITE);

    int sum = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            sum += grid[y][x];
        }
    }
    std::string sum_str = std::to_string(sum);

    int index = highscores_len;
    for (int i = 0; i < highscores_len; i++)
    {
        if (sum > highscores[i])
        {
            index = i;
            break;
        }
    }

    if (index < 3)
    {
        drawString3x5(45, 48, "TOP", SSD1306_WHITE, oled);
        drawString3x5(60, 48, "SCORE!", SSD1306_WHITE, oled);
        if (index == 0)
        {
            renderGameOverLine(line_top, SSD1306_WHITE, 1, sum_str, oled);
            // handle case where there is only one high score
            if (highscores_len >= 1)
                renderGameOverLine(line_top + line_height, SSD1306_WHITE, 2, std::to_string(highscores[0]), oled);
            if (highscores_len >= 2)
                renderGameOverLine(line_top + line_height * 2, SSD1306_WHITE, 3, std::to_string(highscores[1]), oled);
        }
        else if (index == 1)
        {
            renderGameOverLine(line_top, SSD1306_WHITE, 1, std::to_string(highscores[0]), oled);
            renderGameOverLine(line_top + line_height, SSD1306_WHITE, 2, sum_str, oled);
            // handle case where there is only one high score
            if (highscores_len >= 2)
                renderGameOverLine(line_top + line_height * 2, SSD1306_WHITE, 3, std::to_string(highscores[1]), oled);
        }
        else if (index == 2)
        {
            renderGameOverLine(line_top, SSD1306_WHITE, 1, std::to_string(highscores[0]), oled);
            renderGameOverLine(line_top + line_height, SSD1306_WHITE, 2, std::to_string(highscores[1]), oled);
            renderGameOverLine(line_top + line_height * 2, SSD1306_WHITE, 3, sum_str, oled);
        }
    }
    else
    {
        renderGameOverLine(line_top, SSD1306_WHITE, 1, std::to_string(highscores[0]), oled);
        renderGameOverLine(line_top + line_height, SSD1306_WHITE, 2, std::to_string(highscores[1]), oled);
        renderGameOverLine(line_top + line_height * 2, SSD1306_WHITE, 3, std::to_string(highscores[2]), oled);
        renderGameOverLine(line_top + line_height * 3, SSD1306_WHITE, index + 1, sum_str, oled);
    }

    const int flash_line_top = line_top + line_height * min(index, 3);

    if (gameOverMode)
    {
        oled.fillRect(35, flash_line_top - 2, 57, 9, SSD1306_WHITE);
        renderGameOverLine(flash_line_top, SSD1306_BLACK, index + 1, sum_str, oled);
        oled.display();
    }
    else
    {
        oled.fillRect(35, flash_line_top - 2, 57, 9, SSD1306_BLACK);
        renderGameOverLine(flash_line_top, SSD1306_WHITE, index + 1, sum_str, oled);
        oled.display();
    }
}