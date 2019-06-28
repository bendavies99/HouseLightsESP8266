#ifndef AUDIOMODEANIMATION_H
#define AUDIOMODEANIMATION_H

#define BUFFER_LEN 1024

#include "Animation.h"
#include <Adafruit_NeoPixel.h>
#include "globals.h"

namespace
{
  class AudioModeAnimation : public Animation
  {
  public:
     virtual inline void loop(Adafruit_NeoPixel *strip)
     {
      int packetSize = g_Port->parsePacket();
      if (packetSize)
      {
        int len = g_Port->read(m_PacketBuffer, BUFFER_LEN);
        for (int i = 0; i < len; i += 4)
        {
          m_PacketBuffer[len] = 0;
          m_N = m_PacketBuffer[i];
          strip->setPixelColor(m_N, (uint8_t)m_PacketBuffer[i + 1], (uint8_t)m_PacketBuffer[i + 2], (uint8_t)m_PacketBuffer[i + 3]);
        }
        strip->show();
      }
     };
   private:
    char m_PacketBuffer[BUFFER_LEN];
    uint8_t m_N = 0;
  
  };
} // namespace
#endif
