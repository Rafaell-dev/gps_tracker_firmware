#ifndef GPS_H
#define GPS_H

#include <stdint.h>

struct Location {
    float latitude;
    float longitude;
    float altitude;
    float speed;
    float hdop;
    int satellites;
    unsigned long timestamp;
};

void gps_begin();
bool gps_read(Location* loc);

#endif // GPS_H
