#ifndef OTATASK_H
#define OTATASK_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "globals.h"

class OTATask
{
public:
    void loop();
    void setup();
};

#endif