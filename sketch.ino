/**
 * @file sketch.ino
 * @brief Main application for Libelium Smart Parking.
 * @author YOUR FULL NAME
 */

#include <Arduino.h>
#include <ModestIoT.h>

#include "SmartParkingDevice.h"

// Create the main device instance
SmartParkingDevice parkingDevice;

/**
 * @brief Initializes the application.
 */
void setup() {

    Serial.begin(115200);

    parkingDevice.begin();
}

/**
 * @brief Executes the device behavior.
 */
void loop() {

    parkingDevice.update();

    delay(10);
}
