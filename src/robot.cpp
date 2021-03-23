#include "robot.hpp"

#include "led.hpp"

#include "Arduino.h"

using namespace piksel;

void Robot::init() {
    std::unique_ptr<Output> ledPtr(new Led(*this));
    mOutputs.push_back(std::move(ledPtr));

    setup();
}

void Robot::update() {
    loop();

    for (auto&& output : mOutputs) {
        output->update();
    }
}

void Robot::draw(Graphics& g) {
    g.push();

    g.fill(mColor);
    g.rectMode(DrawMode::CENTER);
    g.rotate(mRotation * PI / 180.0f);
    g.translate(mPosition.x, mPosition.y);
    g.noStroke();
    g.rect(0.0f, 0.0f, mWidth, mHeight);

    for (auto&& output : mOutputs) {
        output->draw(g);
    }

    g.pop();
}
