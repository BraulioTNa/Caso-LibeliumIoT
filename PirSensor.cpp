
/**
 * @file PirSensor.cpp
 * @brief Implementation of the PIR motion sensor.
 */

#include <Arduino.h>
#include "PirSensor.h"

PirSensor::PirSensor(
    int pin,
    EventHandler* handler
) : Sensor(pin, handler),
    lastState(false) {

    pinMode(this->pin, INPUT);

    lastState = digitalRead(this->pin) == HIGH;
}

/**
 * @brief Checks whether motion has changed.
 */
void PirSensor::update() {

    bool currentState = digitalRead(pin) == HIGH;

    if (currentState != lastState) {

        lastState = currentState;

        if (currentState) {
            on(Event(MOTION_DETECTED_EVENT));
        }
        else {
            on(Event(MOTION_STOPPED_EVENT));
        }
    }
}

/**
 * @brief Returns the current motion state.
 */
bool PirSensor::isMotionDetected() const {
    return lastState;
}

/**
 * @brief Processes incoming sensor events.
 */
void PirSensor::processEvent(Event& event) {

    if (event.identifier ==
        Sensor::MEASURE_DATA_REQUESTED_EVENT_IDENTIFIER) {

        update();
    }
}
