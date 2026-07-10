#include "telemetry.h"
#include "../config/config.h"
#include <ArduinoJson.h>

void telemetry_create(Telemetry* telemetry, const Location* loc) {
    telemetry->deviceId = DEVICE_ID;
    telemetry->timestamp = loc->timestamp;
    telemetry->latitude = loc->latitude;
    telemetry->longitude = loc->longitude;
    telemetry->altitude = loc->altitude;
    telemetry->speed = loc->speed;
    telemetry->satellites = loc->satellites;
    telemetry->hdop = loc->hdop;
    telemetry->temperature = 0.0; // Sem sensor real no momento
    telemetry->battery_mv = 0;    // Sem leitura de bateria no momento
}

String telemetry_to_json(const Telemetry* telemetry) {
    JsonDocument doc;

    doc["device_id"] = telemetry->deviceId;
    doc["timestamp"] = telemetry->timestamp;
    
    JsonObject gps = doc["gps"].to<JsonObject>();
    gps["lat"] = telemetry->latitude;
    gps["lng"] = telemetry->longitude;
    gps["altitude"] = telemetry->altitude;
    gps["speed"] = telemetry->speed;
    gps["satellites"] = telemetry->satellites;
    gps["hdop"] = telemetry->hdop;

    JsonObject sensors = doc["sensors"].to<JsonObject>();
    sensors["temperature"] = telemetry->temperature;
    sensors["battery_mv"] = telemetry->battery_mv;

    String payload;
    serializeJson(doc, payload);
    return payload;
}
