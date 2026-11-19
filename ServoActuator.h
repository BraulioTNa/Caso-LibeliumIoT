
#ifndef SERVO_ACTUATOR_H
#define SERVO_ACTUATOR_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <ModestIoT.h>

/**
 * @file ServoActuator.h
 * @brief Declaration of the parking barrier actuator.
 */

class ServoActuator : public Actuator {

private:
    Servo servo;
    int angle;

public:
    static const int OPEN_COMMAND_ID = 501;
    static const int CLOSE_COMMAND_ID = 502;

    static const Command OPEN_COMMAND;
    static const Command CLOSE_COMMAND;

    explicit ServoActuator(
        int pin,
        CommandHandler* handler = nullptr
    );

    void executeCommand(Command command) override;
    void open();
    void close();
    int getAngle() const;
};

#endif
