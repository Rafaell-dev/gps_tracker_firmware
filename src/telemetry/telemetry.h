#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "../gps/gps.h"
#include <Arduino.h>

struct Telemetry {
    String deviceId;
    unsigned long timestamp;
    float latitude;
    float longitude;
    float altitude;
    float speed;
    int satellites;
    float hdop;
    float temperature;
    int battery_mv;
};

void telemetry_create(Telemetry* telemetry, const Location* loc);
String telemetry_to_json(const Telemetry* telemetry);

#endif
