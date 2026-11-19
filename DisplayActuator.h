
#ifndef DISPLAY_ACTUATOR_H
#define DISPLAY_ACTUATOR_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ModestIoT.h>

/**
 * @file DisplayActuator.h
 * @brief Declaration of the parking LCD actuator.
 */

class DisplayActuator : public Actuator {

private:
    LiquidCrystal_I2C lcd;
    float distance;
    String parkingStatus;

public:
    static const int UPDATE_DISPLAY_COMMAND_ID = 520;

    static const Command UPDATE_DISPLAY_COMMAND;

    explicit DisplayActuator(
        CommandHandler* handler = nullptr
    );

    void init();

    void setParkingInfo(
        float distance,
        String status
    );

    void executeCommand(Command command) override;

};

#endif
