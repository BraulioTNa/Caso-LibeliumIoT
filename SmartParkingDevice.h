
#ifndef SMART_PARKING_DEVICE_H
#define SMART_PARKING_DEVICE_H

#include <Arduino.h>
#include <ModestIoT.h>

#include "UltrasonicSensor.h"
#include "PirSensor.h"
#include "ServoActuator.h"
#include "RgbLedActuator.h"
#include "DisplayActuator.h"

/**
 * @file SmartParkingDevice.h
 * @brief Declaration of the Libelium Smart Parking device.
 */

class SmartParkingDevice : public Device {

private:

    // Sensors
    ParkingUltrasonicSensor ultrasonicSensor;
    PirSensor pirSensor;

    // Actuators
    ServoActuator servoActuator;
    RgbLedActuator rgbLedActuator;
    DisplayActuator displayActuator;

    // Parking configuration
    static constexpr float OCCUPIED_DISTANCE_CM = 50.0f;

    static constexpr unsigned long
        OVERTIME_LIMIT_MS = 96UL * 60UL * 1000UL;

    static constexpr unsigned long
        SAMPLING_INTERVAL_MS = 500UL;

    // Parking states
    enum ParkingState {
        FREE,
        BUSY,
        OVERTIME
    };

    ParkingState currentState;

    unsigned long occupiedSince;
    unsigned long lastSample;

    void evaluateParkingState(float distance);
    void updateActuators();
    String getStateName() const;

public:

    SmartParkingDevice();

    void begin();
    void update();

    void on(Event event) override;
    void handle(Command command) override;

    ParkingState getParkingState() const;
};

#endif
