
/**
 * @file RgbLedActuator.cpp
 * @brief Implementation of the RGB LED actuator.
 */

#include <Arduino.h>
#include "RgbLedActuator.h"

const Command RgbLedActuator::RED_COMMAND(511);
const Command RgbLedActuator::GREEN_COMMAND(512);
const Command RgbLedActuator::BLUE_COMMAND(513);
const Command RgbLedActuator::OFF_COMMAND(514);

RgbLedActuator::RgbLedActuator(
    int redPin,
    int greenPin,
    int bluePin,
    CommandHandler* handler
) : Actuator(redPin, handler),
    greenPin(greenPin),
    bluePin(bluePin) {

    pinMode(pin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    turnOff();
}

void RgbLedActuator::executeCommand(Command command) {

    if (command == RED_COMMAND) {
        setRed();
    }
    else if (command == GREEN_COMMAND) {
        setGreen();
    }
    else if (command == BLUE_COMMAND) {
        setBlue();
    }
    else if (command == OFF_COMMAND) {
        turnOff();
    }
}

void RgbLedActuator::setRed() {
    digitalWrite(pin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
}

void RgbLedActuator::setGreen() {
    digitalWrite(pin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
}

void RgbLedActuator::setBlue() {
    digitalWrite(pin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
}

void RgbLedActuator::turnOff() {
    digitalWrite(pin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
}