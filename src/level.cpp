#include "level.hpp"
#include "robot.hpp"

Level::Level() {
    b2Vec2 gravity = b2Vec2_zero;
    mWorld.reset(new b2World(gravity));
}

void Level::init() {
    createLevel();

    mRobot.reset(new Robot(mWorld.get()));
    mRobot->init();
}

Level::~Level() {
    for (auto&& frictionJoint : mFrictionJoints) {
        mWorld->DestroyJoint(frictionJoint);
    }

    mRobot.reset(nullptr);
    mWorld.reset(nullptr);
}

void Level::update() {
    mRobot->update();
    mWorld->Step(mTimeStep, mVelocityIterations, mPositionIterations);
}

void Level::draw(piksel::Graphics& g) {
    mRobot->draw(g);
}

void Level::createLevel() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0.0f, 0.0f);
    mLevelBody = mWorld->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0 / 2.0f, 1.0 / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.isSensor = true;

    mLevelBody->CreateFixture(&fixtureDef);
}

void Level::createFrictionJoint(b2Body* body) {
    b2FrictionJointDef frictionJointDef;
    frictionJointDef.bodyA = mLevelBody;
    frictionJointDef.bodyB = body;
    frictionJointDef.collideConnected = false;
    frictionJointDef.maxForce = 1.0f;
    frictionJointDef.maxTorque = 1.0f;
    mFrictionJoints.push_back(static_cast<b2FrictionJoint*>(mWorld->CreateJoint(&frictionJointDef)));
}
