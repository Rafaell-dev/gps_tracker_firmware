#include "gps.h"
#include "../config/config.h"
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <time.h>

static TinyGPSPlus tinyGps;
static HardwareSerial gpsSerial(2);

void gps_begin() {
    Serial.println("[GPS] Inicializando modulo GPS (HardwareSerial 2)...");
    gpsSerial.begin(GPS_BAUD_RATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
}

bool gps_read(Location* loc) {
    bool updated = false;

    // Lê todos os dados disponíveis na UART
    while (gpsSerial.available() > 0) {
        char c = gpsSerial.read();
        
        if (tinyGps.encode(c)) {
            updated = true;
        }
    }

    // Se a localização é válida, preenche a struct
    // Observação: usamos isUpdated() ou simplesmente validamos a localização atual.
    if (updated && tinyGps.location.isValid()) {
        loc->latitude = tinyGps.location.lat();
        loc->longitude = tinyGps.location.lng();
        loc->altitude = tinyGps.altitude.isValid() ? tinyGps.altitude.meters() : 0.0;
        loc->speed = tinyGps.speed.kmph();
        loc->hdop = tinyGps.hdop.isValid() ? tinyGps.hdop.hdop() : 0.0;
        loc->satellites = tinyGps.satellites.value();

        if (tinyGps.date.isValid() && tinyGps.time.isValid()) {
            struct tm timeinfo = {0};
            timeinfo.tm_year = tinyGps.date.year() - 1900;
            timeinfo.tm_mon  = tinyGps.date.month() - 1;
            timeinfo.tm_mday = tinyGps.date.day();
            timeinfo.tm_hour = tinyGps.time.hour();
            timeinfo.tm_min  = tinyGps.time.minute();
            timeinfo.tm_sec  = tinyGps.time.second();
            
            // mktime assumes local time. By default ESP32 is UTC unless setenv("TZ") is called.
            // Since GPS sends UTC time, this correctly creates an Epoch timestamp in UTC.
            loc->timestamp = mktime(&timeinfo);
        } else {
            loc->timestamp = 0; // Se não tiver hora válida, manda 0
        } 
        
        return true;
    }

    return false;
}
