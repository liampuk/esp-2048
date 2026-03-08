#include "buzzer.h"
#include <Arduino.h>

bool buzzerState = false;
int clickCount = 0;
int clickDelay = 100;
int prevClickTime = 0;

void setClick()
{
    clickCount++;
}

void playClick()
{
    unsigned long now = millis();
    if (clickCount > 0 && now - prevClickTime >= clickDelay)
    {
        buzzerState = !buzzerState;
        digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
        clickCount--;
        prevClickTime = now;
    }
}