#include "MQTTClientHandler.h"

#include <utility>

MQTTClientHandler::MQTTClientHandler() : hostname {}, pub {}, sub {}
{};

void MQTTClientHandler::setWiFiClient(WiFiClientSecure& wiFiClientSecure)
{
    mqttClient.setClient(wiFiClientSecure);
}

MQTTClientHandler& MQTTClientHandler::setServerAndPort(const char* server, int port)
{
    mqttClient.setServer(server, port);
    return *this;
}

MQTTClientHandler& MQTTClientHandler::setHostname(const char* hostname)
{
    this->hostname = hostname;
    return *this;
}

MQTTClientHandler& MQTTClientHandler::setPublishTopic(const char* pub)
{
    this->pub = pub;
    return *this;
}

MQTTClientHandler& MQTTClientHandler::setSubscribeTopic(const char* sub)
{
    this->sub = sub;
    return *this;
}

void MQTTClientHandler::connectAndSubscribe()
{
    Serial.println("Connecting to server");

    while (!mqttClient.connect(hostname)) {delay(100);}

    mqttClient.subscribe(sub, 0);

    Serial.println("Server connection established");
}

void MQTTClientHandler::setCallback(std::function<void(char*, uint8_t*, unsigned int)> callback)
{
    mqttClient.setCallback(std::move(callback));
}

void MQTTClientHandler::publish(char* mode)
{
    mqttClient.publish(pub, mode, true);
}

void MQTTClientHandler::maintainConnection()
{
    if (!mqttClient.loop()) { //returns false if client is not connected
        connectAndSubscribe();
        delay(10);
    }
}
