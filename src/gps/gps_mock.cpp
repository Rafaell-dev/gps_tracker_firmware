#include "gps.h"
#include <Arduino.h>

GPSMock::GPSMock() {
    // Valores iniciais simulados (ex: Caruaru, PE)
    currentLocation.latitude = -8.8921f;
    currentLocation.longitude = -36.4972f;
    currentLocation.speed = 0.0f;
    currentLocation.heading = 0;
    currentLocation.timestamp = 1735689600; // Epoch inicial (simulado)
    lastUpdate = 0;
}

void GPSMock::begin() {
    Serial.println("[GPS] GPS Mock inicializado.");
}

Location GPSMock::getLocation() {
    unsigned long currentMillis = millis();
    
    // Atualiza a cada chamada, na prática será chamado a cada 5s pelo main
    currentLocation.latitude += 0.0001f;
    currentLocation.longitude += 0.0001f;
    currentLocation.speed = random(0, 101); // 0 - 100 km/h
    currentLocation.heading = random(0, 361); // 0 - 360 graus
    
    // Atualiza o timestamp (simulado adicionando 5 segundos se chamado a cada 5s)
    // Para um MVP simples, vamos apenas usar o tempo de execução para somar ao epoch base
    // Ou simplesmente adicionar os milissegundos passados desde a última atualização
    if (lastUpdate > 0) {
        currentLocation.timestamp += (currentMillis - lastUpdate) / 1000;
    }
    lastUpdate = currentMillis;

    Serial.println("[GPS] Latitude: " + String(currentLocation.latitude, 4));
    Serial.println("[GPS] Longitude: " + String(currentLocation.longitude, 4));

    return currentLocation;
}
