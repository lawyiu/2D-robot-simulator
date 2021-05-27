#ifndef PINS_CONTROLLER_HPP
#define PINS_CONTROLLER_HPP

#include <stdint.h>
#include <vector>

#include "pinDirection.hpp"

enum class PinType { DIGITAL, ANALOG };
enum class ValueType { DIGITAL, ANALOG };

struct Pin {
    uint32_t number;
    PinType type;
    PinDirection direction;
    ValueType valueType;
    uint32_t value;
};

class PinsController {
public:
    // Default to 100 pins.
    PinsController() : mPins(100) {}
    PinsController(int numPins) : mPins(numPins) {}

    void setPin(Pin pin);
    void setPinType(uint32_t pinNum, PinType type);
    void setPinDirection(uint32_t pinNum, PinDirection direction);
    void setPinValue(uint32_t pinNum, uint32_t value, ValueType valueType);

    Pin getPin(uint32_t pinNum);
    PinType getPinType(uint32_t pinNum);
    PinDirection getPinDirection(uint32_t pinNum);
    ValueType getPinValueType(uint32_t pinNum);
    uint32_t getPinValue(uint32_t pinNum);

private:
    std::vector<Pin> mPins;
};

#endif /* PINS_CONTROLLER_HPP */
