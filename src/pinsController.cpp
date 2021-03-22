#include "pinsController.hpp"

void PinsController::setPin(Pin pin) { mPins[pin.number] = pin; }

void PinsController::setPinType(uint32_t pinNum, PinType type) {
    Pin pin = getPin(pinNum);
    pin.type = type;
    setPin(pin);
}

void PinsController::setPinDirection(uint32_t pinNum, PinDirection direction) {
    Pin pin = getPin(pinNum);
    pin.direction = direction;
    setPin(pin);
}
void PinsController::setPinValue(uint32_t pinNum, uint32_t value) {
    Pin pin = getPin(pinNum);
    pin.value = value;
    setPin(pin);
}

Pin PinsController::getPin(uint32_t pinNum) {
    Pin pin = mPins[pinNum];

    if (pin.number != pinNum) {
        pin.number = pinNum;
    }

    return pin;
}

PinType PinsController::getPinType(uint32_t pinNum) { return getPin(pinNum).type; }

PinDirection PinsController::getPinDirection(uint32_t pinNum) { return getPin(pinNum).direction; }

uint32_t PinsController::getPinValue(uint32_t pinNum) { return getPin(pinNum).value; }
