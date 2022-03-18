#pragma once

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <pgmspace.h>

class MQTTClientHandler
{
private:
    char* hostname;
    char* pub;
    char* sub;
public:
    MQTTClientHandler();

    PubSubClient mqttClient {};

    void setWiFiClient(WiFiClientSecure& wiFiClientSecure);

    MQTTClientHandler& setServerAndPort(char* server, int port);

    MQTTClientHandler& setHostname(char* hostname);

    MQTTClientHandler& setPublishTopic(char* pub);

    MQTTClientHandler& setSubscribeTopic(char* sub);

    void connectAndSubscribe();

    void setCallback(std::function<void(char *,uint8_t *,unsigned int)> callback);

    void publish(char* payload);

    void maintainConnection();
};
