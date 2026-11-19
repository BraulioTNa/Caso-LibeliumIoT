
#ifndef RGB_LED_ACTUATOR_H
#define RGB_LED_ACTUATOR_H

#include <Arduino.h>
#include <ModestIoT.h>

/**
 * @file RgbLedActuator.h
 * @brief Declaration of the RGB LED actuator.
 */

class RgbLedActuator : public Actuator {

private:
    int greenPin;
    int bluePin;

public:
    static const int RED_COMMAND_ID = 511;
    static const int GREEN_COMMAND_ID = 512;
    static const int BLUE_COMMAND_ID = 513;
    static const int OFF_COMMAND_ID = 514;

    static const Command RED_COMMAND;
    static const Command GREEN_COMMAND;
    static const Command BLUE_COMMAND;
    static const Command OFF_COMMAND;

    RgbLedActuator(
        int redPin,
        int greenPin,
        int bluePin,
        CommandHandler* handler = nullptr
    );

    void executeCommand(Command command) override;

    void setRed();
    void setGreen();
    void setBlue();
    void turnOff();
};

#endif
