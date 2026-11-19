
/**
 * @file ServoActuator.cpp
 * @brief Implementation of the servo actuator.
 */

#include <Arduino.h>
#include "ServoActuator.h"

const Command ServoActuator::OPEN_COMMAND(
    ServoActuator::OPEN_COMMAND_ID
);

const Command ServoActuator::CLOSE_COMMAND(
    ServoActuator::CLOSE_COMMAND_ID
);

ServoActuator::ServoActuator(
    int pin,
    CommandHandler* handler
) : Actuator(pin, handler),
    angle(0) {

    servo.attach(pin);
    servo.write(angle);
}

void ServoActuator::executeCommand(Command command) {

    if (command == OPEN_COMMAND) {
        open();
    }
    else if (command == CLOSE_COMMAND) {
        close();
    }
}


void ServoActuator::open() {
    angle = 90;
    servo.write(angle);
}

void ServoActuator::close() {
    angle = 0;
    servo.write(angle);
}

int ServoActuator::getAngle() const {
    return angle;
}
