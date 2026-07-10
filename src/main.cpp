#include <Arduino.h>
#include "config/config.h"
#include "gps/gps.h"
#include "telemetry/telemetry.h"
#include "network/api_client.h"

unsigned long lastSendTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n[SYSTEM] Iniciando Firmware Rastreador GPS...");

    network_begin();
    gps_begin();
}

void loop() {
    Location location;

    if (gps_read(&location)) {
        
        if (millis() - lastSendTime >= MAIN_LOOP_INTERVAL_MS) {
            lastSendTime = millis();
            
            Telemetry telemetry;
            
            telemetry_create(&telemetry, &location);
            
            api_send(&telemetry);
        }
    }
}