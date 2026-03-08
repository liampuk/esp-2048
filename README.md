# ESP-32 2048 Game

- See online: https://wokwi.com/projects/448625876499333121
- To build, install [PlatformIO](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode) and [Wokwi Simulator](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode).

> [!NOTE]  
> This project uses different pins for hardware esp32 and the Wokwi simulator, as I'm using SPI on hardware but the Wokwi oled module only supports SPI. Comment out the relavent code blocks to build for either.

![IMG_6640](https://github.com/user-attachments/assets/cac80b4c-a4d0-4472-a9b1-754636e443fa)

## ESP-32 Pinout

                    ┌─────────────────────────────────────┐
                    │         XIAO ESP32-C3               │
                    │                                     │
    Buttons         │   GPIO 2  ───  D (right)            │
    (INPUT_PULLUP)  │   GPIO 3  ───  S (down)             │
                    │   GPIO 4  ───  A (left)             │
                    │   GPIO 5  ───  Restart              │
                    │   GPIO 6  ───  W (up)               │
                    │   GPIO 21  ───  Menu                │
                    │                                     │
    OLED (SPI)      │   GPIO 8  ───  CLK                  │
                    │   GPIO 9  ───  DC (data/command)    │
                    │   GPIO 10 ───  MOSI                 │
                    │   GPIO 20 ───  RST (reset)          │
                    │   (CS = -1, not connected)          │
                    │                                     │
    Buzzer          │   GPIO 7 ───  Buzzer (click output) │
                    │                                     │
                    └─────────────────────────────────────┘

## OLED pinout

- SCL = CLK
- SDA = MOSI
