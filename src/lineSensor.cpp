#include "lineSensor.hpp"
#include "pinsController.hpp"
#include "robot.hpp"
#include "tape.hpp"
#include "iostream"

using namespace piksel;

LineSensor::LineSensor(Robot& robot, uint32_t pin, glm::vec2 position)
    : Input(robot), mPinNum(pin), mPinsCtrl(robot.getPinsController()) {
    mPosition = robot.getPosition() + position;
    mWorld = robot.getWorld();
    createBody();
    createJoint();
}

LineSensor::~LineSensor() {
    mWorld->DestroyJoint(mWeldJoint);
    mWorld->DestroyBody(mBody);
}

void LineSensor::createBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(mPosition.x, mPosition.y);

    b2BodyUserData bodyUserData;
    Contactable* contactable = this;
    bodyUserData.pointer = reinterpret_cast<uintptr_t>(contactable);
    bodyDef.userData = bodyUserData;

    mBody = mWorld->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(mWidth / 2.0f, mHeight / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 50.0f; // 5 grams
    fixtureDef.isSensor = true;

    mBody->CreateFixture(&fixtureDef);
}

void LineSensor::createJoint() {
    // Attach to robot body
    b2Body* robotBody = mRobot.getBody();
    b2WeldJointDef weldJointDef;
    b2Vec2 position(mPosition.x, mPosition.y);
    weldJointDef.Initialize(mBody, robotBody, position);
    weldJointDef.collideConnected = false;

    mWeldJoint = mWorld->CreateJoint(&weldJointDef);
}

void LineSensor::setState(bool state) {
    mPinsCtrl.setPinValue(mPinNum, state, ValueType::DIGITAL);
}

void LineSensor::update() {
    mState = mPinsCtrl.getPinValue(mPinNum);
}

void LineSensor::draw(Graphics& g) {
    g.push();

    g.stroke(mColor);

    if (!mState) {
        g.noFill();
    } else {
        g.fill(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    }

    g.rectMode(DrawMode::CENTER);

    b2Vec2 sensorPos = mBody->GetPosition();
    g.translate(sensorPos.x, sensorPos.y);
    g.rotate(mBody->GetAngle());
    // Overdraw by 0.01f to account for box2D "skin" thinkness
    g.rect(0.0f, 0.0f, mWidth + 0.01f, mHeight + 0.01f);
    g.pop();
}

void LineSensor::contactBegin(Contactable& other) {
    if (typeid(other) == typeid(Tape)) {
        setState(true);
    }
}

void LineSensor::contactEnd(Contactable& other) {
    if (typeid(other) == typeid(Tape)) {
        setState(false);
    }
}
