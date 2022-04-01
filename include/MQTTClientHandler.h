#pragma once

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <pgmspace.h>

class MQTTClientHandler
{
private:
    const char* hostname;
    const char* pub;
    const char* sub;
public:
    MQTTClientHandler();

    PubSubClient mqttClient {};

    void setWiFiClient(WiFiClientSecure& wiFiClientSecure);

    MQTTClientHandler& setServerAndPort(const char* server, int port);

    MQTTClientHandler& setHostname(const char* hostname);

    MQTTClientHandler& setPublishTopic(const char* pub);

    MQTTClientHandler& setSubscribeTopic(const char* sub);

    void connectAndSubscribe();

    void setCallback(std::function<void(char *,uint8_t *,unsigned int)> callback);

    void publish(char* payload);

    void maintainConnection();
};
