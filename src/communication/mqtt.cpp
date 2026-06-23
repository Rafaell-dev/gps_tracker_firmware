#include "mqtt.h"

void MQTTMock::begin() {
    Serial.println("[MQTT] MQTT Mock inicializado. Nenhuma conexao real sera feita.");
}

bool MQTTMock::publish(const String& topic, const String& payload) {
    Serial.println("[MQTT] Payload criado");
    Serial.println("MQTT PAYLOAD (" + topic + "):");
    Serial.println(payload);
    return true; // Simula sucesso sempre
}
