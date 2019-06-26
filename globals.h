#ifndef LIGHTS_GLOBALS_H_HAPPY
#define LIGHTS_GLOBALS_H_HAPPY

enum LightAnimation
{
    COLORWIPE = 0,
    THEATERCHASE = 1,
    RAINBOW = 2,
    SOLID = 3
};

extern LightAnimation g_CurrentAnimation;
extern int g_Brightness;
extern bool g_IsOnline;
extern bool g_Reset;

#endif
