#include "storage.h"

void StorageMock::begin() {
    Serial.println("[STORAGE] Storage Mock inicializado.");
}

bool StorageMock::saveEvent(const String& payload) {
    Serial.println("[STORAGE] Evento salvo na memoria mockada (nao persistente).");
    return true; // Simula sucesso sempre
}
