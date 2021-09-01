#include "level.hpp"
#include "robot.hpp"
#include "tape.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <json11/json11.hpp>

using namespace std;
using namespace json11;

Level::Level() {
    b2Vec2 gravity = b2Vec2_zero;
    mWorld.reset(new b2World(gravity));
    mWorld->SetContactListener(&mContactListener);
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

    clearLevel();
    mRobot.reset(nullptr);
    mWorld.reset(nullptr);
}

void Level::update() {
    for (auto&& tape : mTapes) {
        tape->update();
    }

    mRobot->update();
    mWorld->Step(mTimeStep, mVelocityIterations, mPositionIterations);
}

void Level::draw(piksel::Graphics& g) {
    for (auto&& tape : mTapes) {
        tape->draw(g);
    }

    mRobot->draw(g);
}

string Level::loadLevel(string filePath) {
    clearLevel();

    string err;
    ifstream levelFile(filePath);

    if (levelFile.fail()) {
        err += filePath + " does not exist!";
    } else {
        stringstream buf;
        buf << levelFile.rdbuf();

        auto json = Json::parse(buf.str(), err);
        if (err.empty()) {
            auto tapes = json["tapes"];

            for (auto tape : tapes.array_items()) {
                string tapeErr;
                Json::shape shape = {{"x", Json::NUMBER},
                                     {"y", Json::NUMBER},
                                     {"width", Json::NUMBER},
                                     {"height", Json::NUMBER},
                                     {"angle", Json::NUMBER}};

                if (tape.has_shape(shape, tapeErr)) {
                    glm::vec2 tapePos(tape["x"].number_value(), tape["y"].number_value());
                    float angle = glm::radians(tape["angle"].number_value());
                    float width = tape["width"].number_value();
                    float height = tape["height"].number_value();

                    unique_ptr<Tape> tape = unique_ptr<Tape>(new Tape(*(mWorld.get()), tapePos, angle, width, height));
                    mTapes.push_back(move(tape));
                } else {
                    cerr << "Parsing Tape failed: " << tapeErr << endl;
                }
            }
        }
    }

    return err;
}

void Level::clearLevel() {
    mTapes.clear();
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
