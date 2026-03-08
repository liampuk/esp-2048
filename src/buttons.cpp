#include "buttons.h"
#include <Wire.h>

const unsigned long debounceDelay = 30; // ms
const unsigned long initialDelay = 500; // ms before auto-repeat
const unsigned long repeatDelay = 100;  // ms between repeats

// ## START HARDWARE ##
Button wButton = {6, false, false, 0, 0, false};
Button aButton = {4, false, false, 0, 0, false};
Button sButton = {3, false, false, 0, 0, false};
Button dButton = {2, false, false, 0, 0, false};

Button menuButton = {21, false, false, 0, 0, false};
Button restartButton = {5, false, false, 0, 0, false};
// ## END HARDWARE ##

// ## START WOKWI ##
// Button wButton = {9, false, false, 0, 0, false};
// Button aButton = {20, false, false, 0, 0, false};
// Button sButton = {8, false, false, 0, 0, false};
// Button dButton = {10, false, false, 0, 0, false};

// Button menuButton = {3, false, false, 0, 0, false};
// Button restartButton = {2, false, false, 0, 0, false};
// ## END WOKWI ##

int activeButtonPin = -1;

bool read_button(Button &btn)
{
    bool raw = digitalRead(btn.pin) == LOW;
    unsigned long now = millis();

    // debounce
    if (raw != btn.lastRead)
    {
        btn.lastChange = now;
        btn.lastRead = raw;
    }
    if ((now - btn.lastChange) > debounceDelay)
    {
        if (btn.state != raw)
        {
            btn.state = raw;
            if (btn.state)
            {
                // first press
                btn.lastRepeat = now;
                btn.pressedEventFired = false;
                activeButtonPin = btn.pin;
                return true; // fire immediately
            }
            else
            {
                // Released
                if (activeButtonPin == btn.pin)
                    activeButtonPin = -1;
            }
        }
    }

    // handle key repeat
    if (btn.state && activeButtonPin == btn.pin)
    {
        if (!btn.pressedEventFired)
        {
            if (now - btn.lastRepeat >= initialDelay)
            {
                btn.lastRepeat = now;
                btn.pressedEventFired = true;
                return true;
            }
        }
        else
        {
            if (now - btn.lastRepeat >= repeatDelay)
            {
                btn.lastRepeat = now;
                return true;
            }
        }
    }

    return false;
}