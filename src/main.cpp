#include <Arduino.h>
#include "config/config.h"
#include "gps/gps.h"
#include "telemetry/telemetry.h"
#include "communication/mqtt.h"
#include "storage/storage.h"

// Instâncias dos Mocks
GPSMock gps;
MQTTMock mqtt;
StorageMock storage;

// Variável para armazenar o payload gerado antes do envio
String currentPayload = "";

// Definição dos Estados
enum SystemState {
    GPS_ACTIVE,
    TRANSMIT,
    SLEEP
};

SystemState currentState = GPS_ACTIVE;
unsigned long sleepStartTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000); // Aguarda a serial estabilizar
    
    Serial.println();
    Serial.println("[BOOT] Dispositivo iniciado");

    gps.begin();
    mqtt.begin();
    storage.begin();
    
    // Inicializa a semente para o random (GPS Mock)
    randomSeed(analogRead(0));
}

void loop() {
    switch (currentState) {
        case GPS_ACTIVE: {
            Serial.println("\n--- Iniciando Ciclo ---");
            Location loc = gps.getLocation();
            
            // Simula valores de bateria e sinal para o MVP
            int mockBatteryMv = 3800; // 3.8V
            int mockRssi = -70;       // Bom sinal
            
            currentPayload = Telemetry::generatePayload(DEVICE_ID, loc, mockBatteryMv, mockRssi);
            
            currentState = TRANSMIT;
            break;
        }
        
        case TRANSMIT: {
            bool success = mqtt.publish("tracker/data", currentPayload);
            
            if (!success) {
                // Em caso de falha de transmissão, salva offline
                storage.saveEvent(currentPayload);
            }
            
            currentState = SLEEP;
            sleepStartTime = millis();
            Serial.println("[SLEEP] Aguardando proximo ciclo...");
            break;
        }
        
        case SLEEP: {
            if (millis() - sleepStartTime >= MAIN_LOOP_INTERVAL_MS) {
                currentState = GPS_ACTIVE;
            }
            // Pequeno delay para evitar watch dog reset e uso alto de CPU
            delay(100);
            break;
        }
    }
}