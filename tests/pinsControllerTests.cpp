#include "gtest/gtest.h"

#include "pinsController.hpp"

TEST(PinsControllerTest, GettingDefault) {
    PinsController pins;
    Pin result = pins.getPin(42);

    EXPECT_EQ(42, result.number);
    EXPECT_EQ(PinType::DIGITAL, result.type);
    EXPECT_EQ(PinDirection::INPUT, result.direction);
    EXPECT_FLOAT_EQ(0.0f, result.value);

    EXPECT_EQ(PinType::DIGITAL, pins.getPinType(42));
    EXPECT_EQ(PinDirection::INPUT,pins.getPinDirection(42));
    EXPECT_FLOAT_EQ(0.0f, pins.getPinValue(42));
}

TEST(PinsControllerTest, SettingAndGetting) {
    PinsController pins;
    Pin pin;

    pin.number = 42;
    pin.type = ANALOG;
    pin.direction = OUTPUT;
    pin.value = 42.0f;

    pins.setPin(pin);

    Pin result = pins.getPin(42);

    EXPECT_EQ(pin.number, result.number);
    EXPECT_EQ(pin.type, result.type);
    EXPECT_EQ(pin.direction, result.direction);
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

    pins.setPinValue(42, 100.0f);

    EXPECT_FLOAT_EQ(100.0f, pins.getPinValue(42));
}
