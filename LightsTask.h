#ifndef LIGHTSTASK_H
#define LIGHTSTASK_H

#include <Adafruit_NeoPixel.h>
#include "ColourWipeAnimation.h"
#include "RainbowAnimation.h"
#include "globals.h"
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

class LightsTask
{
public:
    LightsTask(Adafruit_NeoPixel *strip);
    ~LightsTask();
    void loop();
    void setup();

private:
    Adafruit_NeoPixel *m_Strip;
    ColourWipeAnimation m_ColorWipeAnimation;
    RainbowAnimation m_RainbowAnimation;
    Animation *m_Animation;
};

#endif