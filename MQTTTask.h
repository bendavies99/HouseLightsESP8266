#ifndef MQTTTASK_H
#define MQTTTASK_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "globals.h"
#include "config.h"

class MQTTTask
{
public:
    MQTTTask();
    void loop();
    void setup();
    void reconnect();

private:
    WiFiClient *m_EspClient;
    PubSubClient *m_Client;
};

#endif
