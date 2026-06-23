#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "../gps/gps.h"
#include <Arduino.h>

class Telemetry {
public:
    static String generatePayload(const String& deviceId, const Location& loc, int batteryMv, int rssi);
};

#endif // TELEMETRY_H
