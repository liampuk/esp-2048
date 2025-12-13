#pragma once

struct Button
{
    int pin;
    bool state;
    bool lastRead;
    unsigned long lastChange;
    unsigned long lastRepeat;
    bool pressedEventFired;
};

extern Button wButton, aButton, sButton, dButton, menuButton, restartButton;
extern int activeButtonPin;

bool read_button(Button &btn);