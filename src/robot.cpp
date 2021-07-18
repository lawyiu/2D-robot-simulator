#include "robot.hpp"
#include "app.hpp"

#include "lineSensor.hpp"

#include "led.hpp"
#include "L298N_MotorController.hpp"

#include <dlfcn.h>
#include <iostream>
#include <utility>

#define DEFAULT_LIB "./libcode.so"

using namespace piksel;
using namespace std;

Robot::~Robot() {
    unloadCode();

    mInputs.clear();
    mTires.clear();
    mWorld->DestroyBody(mBody);
}

void Robot::createBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(mPosition.x, mPosition.y);
    mBody = mWorld->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(mWidth / 2.0f, mHeight / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    mBody->CreateFixture(&fixtureDef);
}

void Robot::addTires() {
    float tireWidth = 0.06f;
    float tireHeight = 0.03f;
    glm::vec4 tireColor(0.30f, 0.30f, 0.30f, 1.0f);

    float halfRobotWidth = mWidth / 2.0f;
    float halfRobotHeight = mHeight / 2.0f;

    float tireWidthOffset = tireWidth / 16.0f;
    float tireHeightOffset = 0.01f;
    float tireRobotOffsetX = halfRobotWidth - tireWidth - tireWidthOffset;
    float tireRobotOffsetY = halfRobotHeight + tireHeightOffset;

    std::pair<glm::vec2, Tire::Side> tirePositions[] = {
        std::make_pair(glm::vec2(-tireRobotOffsetX, tireRobotOffsetY), Tire::RIGHT),
        std::make_pair(glm::vec2(tireRobotOffsetX, tireRobotOffsetY), Tire::RIGHT),
        std::make_pair(glm::vec2(-tireRobotOffsetX, -tireRobotOffsetY), Tire::LEFT),
        std::make_pair(glm::vec2(tireRobotOffsetX, -tireRobotOffsetY), Tire::LEFT)
    };

    for (auto&& tirePos : tirePositions) {
        unique_ptr<Tire> tire(new Tire(*this, tirePos.first, tireWidth, tireHeight, tireColor, tirePos.second));
        mTires.push_back(move(tire));
    }
}

void Robot::addLineSensors() {
    std::pair<glm::vec2, uint32_t> lineSensorPositions[] = {
        std::make_pair(glm::vec2(-mWidth / 2.0 + 0.03f, -0.015f), 6),
        std::make_pair(glm::vec2(-mWidth / 2.0 + 0.03f, 0.0f), 7),
        std::make_pair(glm::vec2(-mWidth / 2.0 + 0.03f, 0.015f), 8)
    };

    for (auto&& lineSensorPos : lineSensorPositions) {
        glm::vec2& sensorPos = lineSensorPos.first;
        uint32_t pinNum = lineSensorPos.second;
        unique_ptr<Input> lineSensorPtr(new LineSensor(*this, pinNum, sensorPos));
        mInputs.push_back(move(lineSensorPtr));
    }
}

void Robot::init() {
    // Robot body needs to be created first since sensors and outputs might depend on it.
    createBody();
    addLineSensors();

    unique_ptr<Output> ledPtr(new Led(*this));
    mOutputs.push_back(move(ledPtr));

    unique_ptr<Output> motorDriverPtr(new L298N_MotorController(*this));
    mOutputs.push_back(move(motorDriverPtr));

    addTires();
    // Set rotation of the robot after adding the tires so that the tires are rotated as well.
    setRotation(mRotation);

    loadCode();

    if (mSetup) {
        mSetup();
    }
}

void Robot::loadCode() {
    char* error;

    mLibHandle = dlopen(DEFAULT_LIB, RTLD_NOW);
    if (!mLibHandle) {
        cerr << "[Robot] Error loading the Arduino code from library: " << dlerror() << endl;
    } else {
        dlerror(); // Clear any existing error
        mSetup = reinterpret_cast<setup_t>(dlsym(mLibHandle, "setup"));

        if ((error = dlerror())) {
            cerr << "[Robot] Could not find setup function: " << error << endl;
        }

        dlerror(); // Clear any existing error
        mLoop = reinterpret_cast<loop_t>(dlsym(mLibHandle, "loop"));

        if ((error = dlerror())) {
            cerr << "[Robot] Could not find loop function: " << error << endl;
        }
    }
}

void Robot::unloadCode() {
    if (mLibHandle) {
        if (dlclose(mLibHandle)) {
            cerr << "[Robot] Could not close the library: " << dlerror() << endl;
        } else {
            mLibHandle = nullptr;
        }
    }
}

void Robot::reloadCode() {
    unloadCode();
    loadCode();

    if (mSetup) {
        mSetup();
    }
}

void Robot::update() {
    if (mLoop) {
        mLoop();
    }

    for (auto&& input : mInputs) {
        input->update();
    }

    for (auto&& output : mOutputs) {
        output->update();
    }
}

void Robot::draw(Graphics& g) {
    g.push();

    g.fill(mColor);
    g.rectMode(DrawMode::CENTER);
    g.noStroke();

    for (auto&& tire : mTires) {
        tire->draw(g);
    }

    for (auto&& input : mInputs) {
        input->draw(g);
    }

    g.translate(getPosition().x, getPosition().y);
    g.rotate(getRotation());

    g.rect(0.0f, 0.0f, mWidth, mHeight);

    for (auto&& output : mOutputs) {
        output->draw(g);
    }

    g.pop();
}

glm::vec2 Robot::getPosition() {
    b2Vec2 position = mBody->GetPosition();
    return glm::vec2(position.x, position.y);
}

glm::vec2 Robot::getHeading() {
    float angleRads = getRotation();
    return glm::normalize(glm::vec2(glm::cos(angleRads), glm::sin(angleRads)));
}

void Robot::setHeading(glm::vec2 heading) {
    float cosTheta = glm::dot(glm::vec2(1.0f, 0.0), heading) / glm::length(heading);
    setRotation(glm::acos(cosTheta));
}

glm::vec2 Robot::getLeftPerpendicularVec() {
    glm::vec2 headingVec = getHeading();
    glm::vec2 perpVec = glm::vec2(headingVec.y, -headingVec.x);

    return perpVec;
}

glm::vec2 Robot::getRightPerpendicularVec() {
    glm::vec2 headingVec = getHeading();
    glm::vec2 perpVec = glm::vec2(-headingVec.y, headingVec.x);

    return perpVec;
}

void Robot::applyForce(float force, Tire::Side side) {
    for (auto&& tire : mTires) {
        if (tire->getSide() == side) {
            tire->applyForce(force);
        }
    }
}
