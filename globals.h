#ifndef LIGHTS_GLOBALS_H_HAPPY
#define LIGHTS_GLOBALS_H_HAPPY
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

enum LightAnimation
{
    COLORWIPE = 0,
    THEATERCHASE = 1,
    RAINBOW = 2,
    SOLID = 3,
    AUDIOMODE = 4
};

extern LightAnimation g_CurrentAnimation;
extern WiFiUDP *g_Port;
extern bool g_HasStarted;
extern int g_Brightness;
extern bool g_IsOnline;
extern bool g_Reset;
extern uint8_t g_Red;
extern uint8_t g_Green;
extern uint8_t g_Blue;

#endif
