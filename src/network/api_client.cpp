#include "api_client.h"
#include "../config/config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

void network_begin() {
    Serial.print("[NETWORK] Conectando ao Wi-Fi ");
    Serial.print(WIFI_SSID);
    
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\n[NETWORK] Wi-Fi conectado!");
    Serial.print("[NETWORK] IP: ");
    Serial.println(WiFi.localIP());
}

bool api_send(const Telemetry* telemetry) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[API] Erro: Wi-Fi desconectado.");
        return false;
    }

    WiFiClientSecure client;
    client.setInsecure(); // Ignora validação de certificado SSL (útil para APIs com HTTPS dinâmico como Cloud Run)

    HTTPClient http;
    http.begin(client, API_URL);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-api-key", API_KEY);

    String jsonPayload = telemetry_to_json(telemetry);
    
    Serial.println("[API] Enviando POST para " API_URL);
    Serial.println(jsonPayload);
    
    int httpResponseCode = http.POST(jsonPayload);
    
    if (httpResponseCode > 0) {
        Serial.print("[API] Resposta HTTP: ");
        Serial.println(httpResponseCode);
        http.end();
        return true;
    } else {
        Serial.print("[API] Erro no POST: ");
        Serial.println(http.errorToString(httpResponseCode));
        http.end();
        return false;
    }
}
