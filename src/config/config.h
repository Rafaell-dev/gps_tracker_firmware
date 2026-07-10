#ifndef CONFIG_H
#define CONFIG_H

// Configurações Gerais
#define DEVICE_ID "TRK0001"

// Configurações de Wi-Fi
#define WIFI_SSID "TPLINK-Rafael"
#define WIFI_PASS "Rafael706"

// Configurações da API
#define API_URL "https://api-telemetria-602423258185.southamerica-east1.run.app/api/v1/telemetry/telemetry"
#define API_KEY "embarcados_2026"

// Configurações do GPS (HardwareSerial 2)
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD_RATE 9600

// Intervalo do Loop Principal (em milissegundos)
#define MAIN_LOOP_INTERVAL_MS 30000

#endif // CONFIG_H
