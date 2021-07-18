#ifndef INPUT_HPP
#define INPUT_HPP

namespace piksel {
class Graphics;
}

class Robot;

class Input {
public:
    virtual ~Input() {}

    virtual void update() {}
    virtual void draw(piksel::Graphics& g) {}

protected:
    Input(Robot& robot) : mRobot(robot) {}

    Robot& mRobot;
};

#endif /* INPUT_HPP */
