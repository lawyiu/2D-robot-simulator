#include "gtest/gtest.h"

#include "pinsController.hpp"

TEST(PinsControllerTest, GettingDefault) {
    PinsController pins;
    Pin result = pins.getPin(42);

    EXPECT_EQ(42, result.number);
    EXPECT_EQ(PinType::DIGITAL, result.type);
    EXPECT_EQ(PinDirection::INPUT, result.direction);
    EXPECT_EQ(ValueType::DIGITAL, result.valueType);
    EXPECT_EQ(0, result.value);

    EXPECT_EQ(PinType::DIGITAL, pins.getPinType(42));
    EXPECT_EQ(PinDirection::INPUT, pins.getPinDirection(42));
    EXPECT_EQ(ValueType::DIGITAL, pins.getPinValueType(42));
    EXPECT_EQ(0, pins.getPinValue(42));
}

TEST(PinsControllerTest, SettingAndGetting) {
    PinsController pins;
    Pin pin;

    pin.number = 42;
    pin.type = PinType::ANALOG;
    pin.direction = OUTPUT;
    pin.valueType = ValueType::ANALOG;
    pin.value = 42;

    pins.setPin(pin);

    Pin result = pins.getPin(42);

    EXPECT_EQ(pin.number, result.number);
    EXPECT_EQ(pin.type, result.type);
    EXPECT_EQ(pin.direction, result.direction);
    EXPECT_EQ(pin.valueType, result.valueType);
    EXPECT_EQ(pin.value, result.value);
}

TEST(PinsControllerTest, SettingAndGettingType) {
    PinsController pins;

    pins.setPinType(42, PinType::ANALOG);

    EXPECT_EQ(PinType::ANALOG, pins.getPinType(42));
}

TEST(PinsControllerTest, SettingAndGettingDirection) {
    PinsController pins;

    pins.setPinDirection(42, PinDirection::OUTPUT);

    EXPECT_EQ(PinDirection::OUTPUT, pins.getPinDirection(42));
}

TEST(PinsControllerTest, SettingAndGettingValue) {
    PinsController pins;

    pins.setPinValue(42, 100, ValueType::ANALOG);

    EXPECT_EQ(100, pins.getPinValue(42));
    EXPECT_EQ(ValueType::ANALOG, pins.getPinValueType(42));
}
