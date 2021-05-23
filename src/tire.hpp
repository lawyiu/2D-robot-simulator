#ifndef TIRE_HPP
#define TIRE_HPP

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <graphics.hpp>

class Robot;

class Tire {
public:
    enum Side { NONE, LEFT, RIGHT };

    /* Position is relative to center of robot.
       Width and height in meters. */
    Tire(Robot& robot, glm::vec2 position, float width, float height, glm::vec4 color, Side side);
    ~Tire();

    void draw(piksel::Graphics& g);

    Side getSide() { return mSide; };

protected:
    void createBody(glm::vec2 position);
    void createJoint();

    Robot& mRobot;
    float mWidth, mHeight;
    glm::vec4 mColor;
    Side mSide;

    b2World& mWorld;
    b2Body* mTireBody;
    b2DistanceJoint* mDistJoint;
};

#endif /* TIRE_HPP */
