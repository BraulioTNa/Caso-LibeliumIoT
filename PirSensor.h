
#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <Arduino.h>
#include <ModestIoT.h>

/**
 * @file PirSensor.h
 * @brief Declaration of the PIR motion sensor.
 */

class PirSensor : public Sensor {

private:
    bool lastState;

    void processEvent(Event& event) override;

public:
    static const int MOTION_DETECTED_EVENT = 302;
    static const int MOTION_STOPPED_EVENT = 303;

    PirSensor(
        int pin,
        EventHandler* handler = nullptr
    );

    void update();
    bool isMotionDetected() const;
};

#endif
