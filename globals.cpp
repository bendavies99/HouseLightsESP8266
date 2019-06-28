#include "globals.h"
LightAnimation g_CurrentAnimation = LightAnimation::RAINBOW;
WiFiUDP *g_Port = new WiFiUDP(); 
int g_Brightness = 255;
bool g_IsOnline = true;
bool g_Reset = false;
bool g_HasStarted = false;
uint8_t g_Red = 255;
uint8_t g_Green = 255;
uint8_t g_Blue = 255;
