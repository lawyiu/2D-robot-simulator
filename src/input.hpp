#ifndef INPUT_HPP
#define INPUT_HPP

namespace piksel {
class Graphics;
}

class Robot;

class Input {
public:
    virtual ~Input() {}

    virtual void update() = 0;
    virtual void draw(piksel::Graphics& g) = 0;

protected:
    Input(Robot& robot) : mRobot(robot) {}

    Robot& mRobot;
};

#endif /* INPUT_HPP */
