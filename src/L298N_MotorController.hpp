#ifndef L298N_MOTOR_CONTROLLER_HPP
#define L298N_MOTOR_CONTROLLER_HPP

#include "output.hpp"

#include "glm/glm.hpp"

class PinsController;
class Pin;

class L298N_MotorController : public Output {
public:
    L298N_MotorController(Robot& robot) : L298N_MotorController(robot, {2, 3, 4, 5, 9, 10}, true) {}
    L298N_MotorController(Robot& robot, bool manualEn) : L298N_MotorController(robot, {2, 3, 4, 5, 9, 10}, manualEn) {}
    L298N_MotorController(Robot& robot, std::initializer_list<uint32_t> pins, bool manualEn);

    void update();
    void draw(piksel::Graphics& g) {};

private:
    void getChannelValues(Pin in1, Pin in2, Pin en, uint32_t& in1Val, uint32_t& in2Val, uint32_t& enVal, bool left);

    PinsController& mPinsCtrl;

    int mMotorIn1PinNum; // Controls left motor direction. Defaults to pin 2.
    int mMotorIn2PinNum; // Controls left motor direction. Defaults to pin 3.
    int mMotorIn3PinNum; // Controls right motor direction. Defaults to pin 4.
    int mMotorIn4PinNum; // Controls right motor direction. Defaults to pin 5.

    int mMotorEnA_PinNum; // Controls left motor speed. Defaults to pin 9.
    int mMotorEnB_PinNum; // Controls right motor speed. Defaults to pin 10.

    bool mManualEn = true; // Signifies if the enable pins for this motor controller will be driven manually

    float mMaxSpeedCM_PerS = 10.0f; // CM/S

    // These bools are used to only print errors once
    bool mWrongIn12PinDirErr = false;
    bool mWrongIn34PinDirErr = false;
    bool mWrongIn12PinTypeErr = false;
    bool mWrongIn34PinTypeErr = false;
    bool mWrongEnA_PinDirErr = false;
    bool mWrongEnB_PinDirErr = false;

    const float mForceIncrement = 5.0f / 255.0f; // Newtons per analog value increment
};

#endif /* L298N_MOTOR_CONTROLLER_HPP */
