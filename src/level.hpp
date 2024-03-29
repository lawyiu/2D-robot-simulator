#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "contactListener.hpp"

#include <box2d/box2d.h>
#include <memory>
#include <vector>
#include <piksel/baseapp.hpp>

class Robot;
class Tape;

class Level {
public:
    Level();
    ~Level();

    void init();
    void update();
    void draw(piksel::Graphics& g);

    // Returns an error string on error or an empty string if no error
    std::string loadLevel(std::string filePath);
    void clearLevel();

    void createFrictionJoint(b2Body* body);

    b2World& getWorld() { return *mWorld; }
    Robot& getRobot() { return *mRobot; }

protected:
    void createLevel();

    const float mTimeStep = 1.0f / 60.0f;
    const int32 mVelocityIterations = 6;
    const int32 mPositionIterations = 2;

    ContactListener mContactListener;

    std::unique_ptr<b2World> mWorld;
    b2Body* mLevelBody;
    std::vector<b2FrictionJoint*> mFrictionJoints;

    std::unique_ptr<Robot> mRobot;
    std::vector<std::unique_ptr<Tape>> mTapes;
};

#endif /* LEVEL_HPP */
