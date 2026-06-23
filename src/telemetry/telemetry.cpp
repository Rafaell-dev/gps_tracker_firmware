#include "telemetry.h"
#include <ArduinoJson.h>

String Telemetry::generatePayload(const String& deviceId, const Location& loc, int batteryMv, int rssi) {
    JsonDocument doc;

    doc["device_id"] = deviceId;
    doc["ts"] = loc.timestamp;
    doc["lat"] = loc.latitude;
    doc["lng"] = loc.longitude;
    doc["spd"] = loc.speed;
    doc["hdg"] = loc.heading;
    doc["bat_mv"] = batteryMv;
    doc["rssi"] = rssi;

    String payload;
    serializeJson(doc, payload);

    return payload;
}
