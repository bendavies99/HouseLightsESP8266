#ifndef COLOURWIPEANIMATION_H
#define COLOURWIPEANIMATION_H

#include "Animation.h"
#include <Adafruit_NeoPixel.h>

namespace
{
class ColourWipeAnimation : public Animation
{
public:
   virtual inline void loop(Adafruit_NeoPixel *strip)
   {
      strip->setPixelColor(m_Index, m_Color);
      strip->show();
      delay(50);
   };
   inline void incrementIndex(int numPixels)
   {
      m_Index++;
      if (m_Index > numPixels)
      {
         if (m_Color == ColourWipeAnimation::RED)
         {
            m_Color = ColourWipeAnimation::GREEN;
         }
         else if (m_Color == ColourWipeAnimation::GREEN)
         {
            m_Color = ColourWipeAnimation::BLUE;
         }
         else if (m_Color == ColourWipeAnimation::BLUE)
         {
            m_Color = ColourWipeAnimation::RED;
         }
         m_Index = 0;
      }
   };

public:
   static const uint32_t RED;
   static const uint32_t GREEN;
   static const uint32_t BLUE;

private:
   uint32_t m_Color = ColourWipeAnimation::RED;
};

const uint32_t ColourWipeAnimation::RED = Adafruit_NeoPixel::Color(255, 0, 0);
const uint32_t ColourWipeAnimation::GREEN = Adafruit_NeoPixel::Color(0, 255, 0);
const uint32_t ColourWipeAnimation::BLUE = Adafruit_NeoPixel::Color(0, 0, 255);
} // namespace
#endif