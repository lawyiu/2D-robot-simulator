#include "robot.hpp"

#include "Arduino.h"

using namespace piksel;

void Robot::init() {
    setup();
}

void Robot::update() {
    loop();
}

void Robot::draw(Graphics& g) {
    g.push();

    g.fill(mColor);
    g.rectMode(DrawMode::CENTER);
    g.rotate(mRotation * PI / 180.0f);
    g.translate(mPosition.x, mPosition.y);
    g.noStroke();
    g.rect(0.0f, 0.0f, mWidth, mHeight);

    g.pop();
}
