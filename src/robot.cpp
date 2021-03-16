#include "robot.hpp"

using namespace piksel;

void Robot::update() {}

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
