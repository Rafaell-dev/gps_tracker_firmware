#ifndef GPS_H
#define GPS_H

struct Location {
    float latitude;
    float longitude;
    float speed;
    int heading;
    unsigned long timestamp;
};

class GPS {
public:
    virtual ~GPS() {}
    virtual void begin() = 0;
    virtual Location getLocation() = 0;
};

class GPSMock : public GPS {
private:
    Location currentLocation;
    unsigned long lastUpdate;

public:
    GPSMock();
    void begin() override;
    Location getLocation() override;
};

#endif // GPS_H
