#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <initializer_list>
#include <stdint.h>

namespace piksel {
class Graphics;
}

class Robot;

class Output {
public:
    virtual ~Output() {}

    virtual void update() = 0;
    virtual void draw(piksel::Graphics& g) = 0;

protected:
    Output(Robot& robot, std::initializer_list<uint32_t> pins) : mRobot(robot) {}

    Robot& mRobot;
};

#endif /* OUTPUT_HPP */
