#ifndef LED_HPP
#define LED_HPP

#include "output.hpp"

#include <glm/glm.hpp>

class Led : public Output {
public:
    Led(Robot& robot) : Led(robot, {13}, glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) {}
    Led(Robot& robot, glm::vec2 position) : Led(robot, {13}, position, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) {}
    Led(Robot& robot, std::initializer_list<uint32_t> pins, glm::vec2 position)
        : Led(robot, pins, position, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) {}
    Led(Robot& robot, std::initializer_list<uint32_t> pins, glm::vec2 position, glm::vec4 color);

    void update() override;
    void draw(piksel::Graphics& g) override;

private:
    glm::vec2 mPosition;
    glm::vec4 mColor;
    int mPinNum;
    bool mState;
};

#endif /* LED_HPP */
