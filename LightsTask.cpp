#include "LightsTask.h"

LightsTask::LightsTask(Adafruit_NeoPixel *strip)
{
    m_Strip = strip;
}
LightsTask::~LightsTask()
{
    delete m_Strip;
}

void LightsTask::setup()
{
    m_Strip->begin();
    m_Strip->show();
}

void LightsTask::loop()
{
    if (g_IsOnline)
    {
        m_Strip->setBrightness(g_Brightness);
        switch (g_CurrentAnimation)
        {
        case LightAnimation::COLORWIPE:
            if (g_Reset)
            {
                m_ColorWipeAnimation.reset(m_Strip);
                g_Reset = false;
            }
            m_ColorWipeAnimation.loop(m_Strip);
            m_ColorWipeAnimation.incrementIndex(m_Strip->numPixels());
            break;
        case LightAnimation::RAINBOW:
            if (g_Reset)
            {
                m_RainbowAnimation.reset(m_Strip);
                g_Reset = false;
            }
            m_RainbowAnimation.loop(m_Strip);
            m_RainbowAnimation.incrementIndex(m_Strip->numPixels());
            break;
        case LightAnimation::AUDIOMODE:
            if (g_Reset)
            {
                    g_Reset = false;
            }
            m_AudioModeAnimation.loop(m_Strip);
            break;
        case LightAnimation::SOLID:
            for(int i = 0; i < m_Strip->numPixels(); i++) {
              m_Strip->setPixelColor(i, g_Red, g_Green, g_Blue);
            }
            m_Strip->show();
            break;
        }
    }
    else
    {
        m_Strip->begin();
        m_Strip->clear();
        m_Strip->show();
    }
}
