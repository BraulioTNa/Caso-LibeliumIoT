
/**
 * @file SmartParkingDevice.cpp
 * @brief Implementation of the Libelium Smart Parking device.
 */

#include <Arduino.h>
#include "SmartParkingDevice.h"

/**
 * @brief Constructs the Smart Parking device.
 */
SmartParkingDevice::SmartParkingDevice()

    : Device(SAMPLING_INTERVAL_MS),

      ultrasonicSensor(5, 18, this),
      pirSensor(19, this),

      servoActuator(13),
      rgbLedActuator(25, 26, 27),
      displayActuator(),

      currentState(FREE),
      occupiedSince(0),
      lastSample(0) {
}
/**
 * @brief Initializes the complete device.
 */
void SmartParkingDevice::begin() {

    Serial.println();
    Serial.println("================================");
    Serial.println("LIBELIUM INC.");
    Serial.println("SMART PARKING SPOT S1");
    Serial.println("Developer: YOUR FULL NAME");
    Serial.println("================================");

    displayActuator.init();

    currentState = FREE;

    updateActuators();

    Serial.println("Device initialized successfully.");
}

/**
 * @brief Updates sensors and parking state.
 */
void SmartParkingDevice::update() {

    unsigned long currentTime = millis();

    // Periodic sensor sampling
    if (currentTime - lastSample >= SAMPLING_INTERVAL_MS) {

        lastSample = currentTime;

        ultrasonicSensor.triggerRead();

        pirSensor.update();
    }

    // Check parking overtime
    if (currentState == BUSY) {

        if (currentTime - occupiedSince >= OVERTIME_LIMIT_MS) {

            currentState = OVERTIME;

            Serial.println("[PARKING] OVERTIME DETECTED");

            updateActuators();
        }
    }
}

/**
 * @brief Receives sensor events.
 */
void SmartParkingDevice::on(Event event) {

    if (event.identifier == ParkingUltrasonicSensor::DISTANCE_UPDATED_EVENT) {

        float distance = ultrasonicSensor.getDistance();

        if (distance >= 0) {

            evaluateParkingState(distance);

        } else {

            Serial.println("[SENSOR] Invalid distance reading");
        }
    }

    else if (event.identifier == PirSensor::MOTION_DETECTED_EVENT) {

        Serial.println("[PIR] Motion detected");
    }

    else if (event.identifier == PirSensor::MOTION_STOPPED_EVENT) {

        Serial.println("[PIR] Motion stopped");
    }
}

/**
 * @brief Evaluates parking occupancy.
 */
void SmartParkingDevice::evaluateParkingState(float distance) {

    Serial.print("[ULTRASONIC] Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    ParkingState previousState = currentState;

    if (distance <= OCCUPIED_DISTANCE_CM) {

        if (currentState == FREE) {

            currentState = BUSY;
            occupiedSince = millis();

            Serial.println("[PARKING] Vehicle detected");
        }
    }
    else {

        currentState = FREE;
        occupiedSince = 0;
    }

    if (previousState != currentState) {

        updateActuators();
    }
}

/**
 * @brief Updates the physical actuators.
 */
void SmartParkingDevice::updateActuators() {

    if (currentState == FREE) {

        rgbLedActuator.handle(
            RgbLedActuator::GREEN_COMMAND
        );

        servoActuator.handle(
            ServoActuator::OPEN_COMMAND
        );
    }

    else if (currentState == BUSY) {

        rgbLedActuator.handle(
            RgbLedActuator::RED_COMMAND
        );

        servoActuator.handle(
            ServoActuator::CLOSE_COMMAND
        );
    }

    else if (currentState == OVERTIME) {

        rgbLedActuator.handle(
            RgbLedActuator::BLUE_COMMAND
        );

        servoActuator.handle(
            ServoActuator::CLOSE_COMMAND
        );
    }

    displayActuator.setParkingInfo(
        ultrasonicSensor.getDistance(),
        getStateName()
    );

    displayActuator.handle(
        DisplayActuator::UPDATE_DISPLAY_COMMAND
    );

    Serial.print("[PARKING] Current state: ");
    Serial.println(getStateName());
}

/**
 * @brief Returns the current parking state name.
 */
String SmartParkingDevice::getStateName() const {

    switch (currentState) {

        case FREE:
            return "FREE";

        case BUSY:
            return "BUSY";

        case OVERTIME:
            return "OVERTIME";
    }

    return "UNKNOWN";
}

/**
 * @brief Handles external commands.
 */
void SmartParkingDevice::handle(Command command) {

    Serial.print("[DEVICE] Command received: ");
    Serial.println(command.identifier);
}

/**
 * @brief Returns the current parking state.
 */
SmartParkingDevice::ParkingState
SmartParkingDevice::getParkingState() const {

    return currentState;
}
