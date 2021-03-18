#ifndef PINS_CONTROLLER_HPP
#define PINS_CONTROLLER_HPP

#include <stdint.h>
#include <vector>

enum PinDirection { INPUT, OUTPUT };

enum PinType { DIGITAL, ANALOG };

struct Pin {
    uint32_t number;
    PinType type;
    PinDirection direction;
    float value;
};

class PinsController {
public:
    // Default to 100 pins.
    PinsController() : mPins(100) {}
    PinsController(int numPins) : mPins(numPins) {}

    void setPin(Pin pin);
    void setPinType(uint32_t pinNum, PinType type);
    void setPinDirection(uint32_t pinNum, PinDirection direction);
    void setPinValue(uint32_t pinNum, float value);

    Pin getPin(uint32_t pinNum);
    PinType getPinType(uint32_t pinNum);
    PinDirection getPinDirection(uint32_t pinNum);
    float getPinValue(uint32_t pinNum);

private:
    std::vector<Pin> mPins;
};

#endif /* PINS_CONTROLLER_HPP */
