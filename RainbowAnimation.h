#ifndef RAINBOWANIM_H
#define RAINBOWANIM_H

#include "Animation.h"
#include <Adafruit_NeoPixel.h>

namespace
{
class RainbowAnimation : public Animation
{
public:
   virtual inline void loop(Adafruit_NeoPixel *strip)
   {
      for (int i = 0; i < strip->numPixels(); i++)
      {
         int pixelHue = m_Index + (i * 65536L / strip->numPixels());
         uint32_t c = strip->gamma32(strip->ColorHSV(pixelHue));
         strip->setPixelColor(i, c);
      }
      strip->show();
      delay(10);
   };
   inline void incrementIndex(int numPixels)
   {
      m_Index += 256;
      if (m_Index > 5 * 65556)
      {
         m_Index = 0;
      }
   };

public:
private:
};
} // namespace
#endif