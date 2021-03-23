#include "led.hpp"

#include "pinsController.hpp"
#include "robot.hpp"

#include <graphics.hpp>
#include <iostream>

using namespace piksel;

Led::Led(Robot& robot, std::initializer_list<uint32_t> pins, glm::vec2 position, glm::vec4 color)
    : Output(robot, pins), mPosition(position), mColor(color), mState(false) {
    mPinNum = *pins.begin();
}

void Led::update() {
    PinsController& pinsCtrl = mRobot.getPinsController();

    if (pinsCtrl.getPinDirection(mPinNum) == PinDirection::OUTPUT) {
        mState = pinsCtrl.getPinValue(mPinNum);
    }
}

void Led::draw(Graphics& g) {
    g.push();

    g.fill(mColor);

    if (mState) {
        g.rect(mPosition.x, mPosition.y, 1.0f, 1.0f);
    }

    g.pop();
}
