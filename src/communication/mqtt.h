#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>

class MQTTClient {
public:
    virtual ~MQTTClient() {}
    virtual void begin() = 0;
    virtual bool publish(const String& topic, const String& payload) = 0;
};

class MQTTMock : public MQTTClient {
public:
    void begin() override;
    bool publish(const String& topic, const String& payload) override;
};

#endif // MQTT_H
