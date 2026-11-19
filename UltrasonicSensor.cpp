
/**
 * @file UltrasonicSensor.cpp
 * @brief Implementation of the ultrasonic sensor.
 */

#include <Arduino.h>
#include "UltrasonicSensor.h"

ParkingUltrasonicSensor::ParkingUltrasonicSensor(
    int triggerPin,
    int echoPin,
    EventHandler* handler
) : Sensor(triggerPin, handler),
    echoPin(echoPin),
    distance(-1.0f) {

    pinMode(pin, OUTPUT);
    pinMode(echoPin, INPUT);
}

/**
 * @brief Reads distance in centimeters.
 */
float ParkingUltrasonicSensor::readDistance() {
    digitalWrite(pin, LOW);
    delayMicroseconds(2);

    digitalWrite(pin, HIGH);
    delayMicroseconds(10);

    digitalWrite(pin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);

    if (duration == 0) {
        distance = -1.0f;
    } else {
        distance = duration * 0.0343f / 2.0f;
    }

    return distance;
}

float ParkingUltrasonicSensor::getDistance() const {
    return distance;
}

void ParkingUltrasonicSensor::triggerRead() {
    readDistance();
    on(Event(DISTANCE_UPDATED_EVENT));
}

void ParkingUltrasonicSensor::processEvent(Event& event) {

    if (event.identifier ==
        Sensor::MEASURE_DATA_REQUESTED_EVENT_IDENTIFIER) {

        readDistance();
        Sensor::on(Event(DISTANCE_UPDATED_EVENT));
    }
}