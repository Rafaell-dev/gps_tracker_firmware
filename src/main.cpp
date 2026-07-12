#include <Arduino.h>
#include "config/config.h"
#include "gps/gps.h"
#include "telemetry/telemetry.h"
#include "network/api_client.h"

unsigned long lastSendTime = 0;
unsigned long lastGpsDebugTime = 0;

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
    } else {
        if (millis() - lastGpsDebugTime >= 5000) {
            lastGpsDebugTime = millis();
            if (gps_chars_processed() < 10) {
                Serial.println("[GPS] Nenhum dado recebido do modulo. Verifique conexoes RX/TX!");
            } else {
                Serial.println("[GPS] Aguardando sinal de satelite...");
            }
        }
    }
}