
#ifndef LIBELIUM_PARKING_ULTRASONIC_SENSOR_H
#define LIBELIUM_PARKING_ULTRASONIC_SENSOR_H

#include <Arduino.h>
#include <ModestIoT.h>

class ParkingUltrasonicSensor : public Sensor {

private:
    int echoPin;
    float distance;

    void processEvent(Event& event) override;

public:
    static const int DISTANCE_UPDATED_EVENT = 301;

    ParkingUltrasonicSensor(
        int triggerPin,
        int echoPin,
        EventHandler* handler = nullptr
    );

    float readDistance();
    float getDistance() const;
    void triggerRead();
};

#endif
