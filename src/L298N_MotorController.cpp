#include "L298N_MotorController.hpp"
#include "pinsController.hpp"
#include "robot.hpp"

#include <iostream>

L298N_MotorController::L298N_MotorController(Robot& robot, std::initializer_list<uint32_t> pins, bool manualEn)
    : Output(robot, pins), mManualEn(manualEn), mPinsCtrl(robot.getPinsController()) {
    if (pins.size() != 6) {
        std::cerr << "[L298N Motor Driver] Wrong number of pins assigned in pin initializer list!\n";
    } else {
        const uint32_t* iter = pins.begin();
        mMotorIn1PinNum = *iter++;
        mMotorIn2PinNum = *iter++;
        mMotorIn3PinNum = *iter++;
        mMotorIn4PinNum = *iter++;
        mMotorEnA_PinNum = *iter++;
        mMotorEnB_PinNum = *iter++;
    }
}

void L298N_MotorController::getChannelValues(Pin in1, Pin in2, Pin en, uint32_t& in1Val, uint32_t& in2Val,
                                             uint32_t& enVal, bool left) {
    bool& wrongInPinDirErr = (left ? mWrongIn12PinDirErr : mWrongIn34PinDirErr);
    bool& wrongInPinTypeErr = (left ? mWrongIn12PinTypeErr : mWrongIn34PinTypeErr);
    bool& wrongEnPinDirErr = (left ? mWrongEnA_PinDirErr : mWrongEnB_PinDirErr);

    if (in1.direction != OUTPUT || in2.direction != OUTPUT) {
        if (!wrongInPinDirErr) {
            std::cerr << "[L298N Motor Driver] Pin direction for motor driver "
                      << (left ? "IN1 and IN2" : "IN3 and IN4") << " pins must be OUTPUT.\n";
            wrongInPinDirErr = true;
        }
    } else if (in1.type != PinType::DIGITAL || in2.type != PinType::DIGITAL) {
        if (!wrongInPinTypeErr) {
            std::cerr << "[L298N Motor Driver] Pin type for motor driver " << (left ? "IN1 and IN2" : "IN3 and IN4")
                      << " pins must be DIGITAL.\n";
            wrongInPinTypeErr = true;
        }
    } else {
        in1Val = in1.value;
        in2Val = in2.value;
    }

    if (mManualEn) {
        if (en.direction != OUTPUT) {
            if (!wrongEnPinDirErr) {
                std::cerr << "[L298N Motor Driver] Pin direction for motor driver " << (left ? "EnA" : "EnB")
                          << " pin must be OUTPUT.\n";
                wrongEnPinDirErr = true;
            }
        } else if (en.valueType == ValueType::DIGITAL) {
            enVal = en.value * 255;
        } else {
            enVal = en.value;
        }
    } else {
        enVal = 255;
    }
}

void L298N_MotorController::update() {
    Pin in1 = mPinsCtrl.getPin(mMotorIn1PinNum);
    Pin in2 = mPinsCtrl.getPin(mMotorIn2PinNum);
    Pin in3 = mPinsCtrl.getPin(mMotorIn3PinNum);
    Pin in4 = mPinsCtrl.getPin(mMotorIn4PinNum);
    Pin enA = mPinsCtrl.getPin(mMotorEnA_PinNum);
    Pin enB = mPinsCtrl.getPin(mMotorEnB_PinNum);

    uint32_t in1Val = 0, in2Val = 0, in3Val = 0, in4Val = 0;
    uint32_t enA_Val = 0, enB_Val = 0;

    getChannelValues(in1, in2, enA, in1Val, in2Val, enA_Val, true);
    getChannelValues(in3, in4, enB, in3Val, in4Val, enB_Val, false);

    float leftForce = 0.0f;
    float rightForce = 0.0f;

    if (in1Val - in2Val == 1) {
        leftForce = mForceIncrement * enA_Val;
    } else if (in1Val - in2Val == -1) {
        leftForce = -mForceIncrement * enA_Val;
    }

    if (in3Val - in4Val == 1) {
        rightForce = mForceIncrement * enB_Val;
    } else if (in3Val - in4Val == -1) {
        rightForce = -mForceIncrement * enB_Val;
    }

    mRobot.applyForce(leftForce, Tire::LEFT);
    mRobot.applyForce(rightForce, Tire::RIGHT);
}
