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
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

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

    m_Client->setServer(mqtt_server, 1883);
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
        if (m_Client->connect(clientId.c_str(), username, mqtt_password))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            m_Client->publish("outTopic", "hello world");
            // ... and resubscribe
            m_Client->subscribe("Lights/Bedroom");
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
    DynamicJsonDocument doc(11175);

    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        return;
    }

    String newState = doc["state"];
    if (newState == String("ON"))
    {
        g_IsOnline = true;
    }
    else if (newState == String("OFF"))
    {
        g_IsOnline = false;
    }
    if (doc["brightness"])
    {
        int newBrightness = (int)doc["brightness"];
        g_Brightness = newBrightness;
    }
    String animationType = doc["effect"];
    if (animationType == String("rainbow"))
    {
        g_CurrentAnimation = LightAnimation::RAINBOW;
    }
    if (animationType == String("colorwipe"))
    {
        g_CurrentAnimation = LightAnimation::COLORWIPE;
    }

    g_Reset = true;
}
