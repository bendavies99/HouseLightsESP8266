#include "MQTTTask.h"
#include "config.h"

void callback(char *topic, byte *payload, unsigned int length);

MQTTTask::MQTTTask()
{
    m_EspClient = new WiFiClient();
    m_Client = new PubSubClient(*m_EspClient);
}

void MQTTTask::setup()
{
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(C_WIFI_SSID);
    IPAddress ip(C_WIFI_IP);
    IPAddress gateway(C_WIFI_GATEWAY);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(C_WIFI_SSID, C_WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    m_Client->setServer(C_MQTT_SERVER, 1883);
    m_Client->setCallback(callback);
}

void MQTTTask::reconnect()
{
    // Loop until we're reconnected
    while (!m_Client->connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (m_Client->connect(clientId.c_str(), C_MQTT_USERNAME, C_MQTT_PASSWORD))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            // ... and resubscribe
            m_Client->subscribe(C_MQTT_LISTEN_TOPIC);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(m_Client->state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void MQTTTask::loop()
{
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WIFI Disconnected");
    }
    if (!m_Client->connected())
    {
        reconnect();
    }
    m_Client->loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    char json[length];
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
        json[i] = (char)payload[i];
    }
    Serial.println();
    DynamicJsonDocument doc(400);

    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        return;
    }

    String newState = doc["state"];
    if (newState == String("ON"))
    {
         if(g_CurrentAnimation == LightAnimation::AUDIOMODE) {
            if(!g_HasStarted) {
              g_Port->begin(7777);
              g_HasStarted = true;
            } else {
              delete g_Port;
              g_Port = new WiFiUDP();
              g_Port->begin(7777);
            }
        }

        g_IsOnline = true;
    }
    else if (newState == String("OFF"))
    {
        if(g_CurrentAnimation == LightAnimation::AUDIOMODE) {
          if(g_HasStarted) {
            g_Port->stop();
          }
        }
        g_IsOnline = false;

    }
    if (doc["brightness"])
    {
        int newBrightness = (int)doc["brightness"];
        g_Brightness = newBrightness;
    }
    if(doc.containsKey("effect")) {
      String animationType = doc["effect"];
      if (animationType == String("rainbow"))
      {
          g_CurrentAnimation = LightAnimation::RAINBOW;
          if(g_HasStarted) {
            g_Port->stop();
          }
      }
      if (animationType == String("colorwipe"))
      {
          g_CurrentAnimation = LightAnimation::COLORWIPE;
          if(g_HasStarted) {
            g_Port->stop();
          }
      }
      if (animationType == String("solid"))
      {
          g_CurrentAnimation = LightAnimation::SOLID;
          if(g_HasStarted) {
            g_Port->stop();
          }
      }
      if (animationType == String("audiomode"))
      {
          g_CurrentAnimation = LightAnimation::AUDIOMODE;
          if(!g_HasStarted) {
            g_Port->begin(7777);
            g_HasStarted = true;
          } else {
            delete g_Port;
            g_Port = new WiFiUDP();
            g_Port->begin(7777);
          }
      }
    }

    g_Reset = true;

    if(doc.containsKey("color")) {
      g_Red = doc["color"]["r"];
      g_Green = doc["color"]["g"];
      g_Blue = doc["color"]["b"];

      g_Reset = false;
    }
}
