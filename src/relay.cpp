#include "relay.h"
#include <Arduino.h>

bool relayState = false;
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
        relayState = !relayState;
        digitalWrite(relayPin, relayState ? HIGH : LOW);
        clickCount--;
        prevClickTime = now;
    }
}