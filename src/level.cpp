#include "level.hpp"
#include "robot.hpp"
#include "tape.hpp"

using namespace std;

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

    tapes.clear();
    mRobot.reset(nullptr);
    mWorld.reset(nullptr);
}

void Level::update() {
    for (auto&& tape : tapes) {
        tape->update();
    }

    mRobot->update();
    mWorld->Step(mTimeStep, mVelocityIterations, mPositionIterations);
}

void Level::draw(piksel::Graphics& g) {
    for (auto&& tape : tapes) {
        tape->draw(g);
    }

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

    float tapeThickness = 0.03f;
    std::pair<glm::vec2, glm::vec2> tapePositions[] = {
        std::make_pair(glm::vec2(0.0f, -1.0f), glm::vec2(3.0f, tapeThickness)),
        std::make_pair(glm::vec2(1.5f, 0.0f), glm::vec2(tapeThickness, 2.0f)),
        std::make_pair(glm::vec2(0.0f, 1.0f), glm::vec2(3.0f, tapeThickness)),
        std::make_pair(glm::vec2(-1.5f, 0.0f), glm::vec2(tapeThickness, 2.0f))
    };

    for (auto&& elm : tapePositions) {
        glm::vec2 tapePos = elm.first;
        glm::vec2 tapeDim = elm.second;
        unique_ptr<Tape> tape = unique_ptr<Tape>(new Tape(*(mWorld.get()), tapePos, tapeDim.x, tapeDim.y));
        tapes.push_back(move(tape));
    }
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
