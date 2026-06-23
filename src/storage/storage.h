#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>

class Storage {
public:
    virtual ~Storage() {}
    virtual void begin() = 0;
    virtual bool saveEvent(const String& payload) = 0;
    // virtual std::vector<String> getEvents() = 0; // Futuro
};

class StorageMock : public Storage {
public:
    void begin() override;
    bool saveEvent(const String& payload) override;
};

#endif // STORAGE_H
