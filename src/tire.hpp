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

    void update() {};
    void draw(piksel::Graphics& g);

    float getRotation() { return mTireBody->GetAngle(); }
    void setRotation(float radians) { mTireBody->SetTransform(mTireBody->GetPosition(), radians); }
    glm::vec2 getHeading();
    b2Vec2 getForwardVelocity();

    Side getSide() { return mSide; };

    void applyForce(float force);

protected:
    void createBody(glm::vec2 position);
    void createJoint(glm::vec2 position);

    Robot& mRobot;
    glm::vec2 mPosition;
    float mWidth, mHeight;
    glm::vec4 mColor;
    Side mSide;

    b2World& mWorld;
    b2Body* mTireBody;
    b2Joint* mWeldJoint;

    const float mMaxSpeed = 0.1f; // Meters per second
};

#endif /* TIRE_HPP */
