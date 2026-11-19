
/**
 * @file DisplayActuator.cpp
 * @brief Implementation of the parking LCD actuator.
 */

#include <Arduino.h>
#include <Wire.h>
#include "DisplayActuator.h"

const Command DisplayActuator::UPDATE_DISPLAY_COMMAND(520);

DisplayActuator::DisplayActuator(
    CommandHandler* handler
) : Actuator(-1, handler),
    lcd(0x27, 16, 2),
    distance(-1.0f),
    parkingStatus("UNKNOWN") {
}

void DisplayActuator::init() {

    Wire.begin(21, 22);

    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("LIBELIUM PARKING");

    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
}

void DisplayActuator::setParkingInfo(
    float newDistance,
    String status
) {

    distance = newDistance;
    parkingStatus = status;
}

void DisplayActuator::executeCommand(Command command) {

    if (command == UPDATE_DISPLAY_COMMAND) {

        lcd.setCursor(0, 0);

        if (distance >= 0) {
            lcd.print("Dist:");
            lcd.print(distance, 1);
            lcd.print(" cm   ");
        }
        else {
            lcd.print("Dist: ERROR     ");
        }

        lcd.setCursor(0, 1);
        lcd.print("Status: ");
        lcd.print(parkingStatus);
        lcd.print("       ");
    }
}
