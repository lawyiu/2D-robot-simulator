#ifndef LINE_SENSOR_HPP
#define LINE_SENSOR_HPP

#include "input.hpp"

#include <glm/glm.hpp>

class PinsController;
class Pin;
class b2World;
class b2Body;
class b2Joint;

class LineSensor : public Input {
public:
    // Position is relative to origin of robot
    LineSensor(Robot& robot, uint32_t pin, glm::vec2 position);
    ~LineSensor();

    // Used to set if the line sensor is over a line or not
    void setState(bool state);

    void update() override;
    void draw(piksel::Graphics& g) override;

private:
    void createBody();
    void createJoint();

    b2World* mWorld;
    b2Body* mBody;
    b2Joint* mWeldJoint;
    PinsController& mPinsCtrl;
    uint32_t mPinNum;
    glm::vec2 mPosition;

    const glm::vec4 mColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    const float mWidth = 0.01f;  // 1 CM
    const float mHeight = 0.01f; // 1 CM
};

#endif /* LINE_SENSOR_HPP */
