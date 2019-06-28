#ifndef ANIMATION_H
#define ANIMATION_H

#include <Adafruit_NeoPixel.h>

class Animation
{
public:
    virtual void loop(Adafruit_NeoPixel *strip) = 0;
    inline void incrementIndex(int numPixels)
    {
        m_Index++;
        if (m_Index > numPixels)
        {
            m_Index = 0;
        }
    };
    inline void reset(Adafruit_NeoPixel *strip)
    {
        m_Index = 0;
        strip->clear();
        strip->show();
    };

protected:
    int m_Index = 0;
};

#endif
