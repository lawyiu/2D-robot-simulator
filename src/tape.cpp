#include "tape.hpp"

#include <box2d/box2d.h>

using namespace piksel;

Tape::Tape(b2World& world, glm::vec2 position, glm::vec4 color, float width, float height)
    : mWorld(world), mPosition(position), mColor(color), mWidth(width), mHeight(height) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(mPosition.x, mPosition.y);

    b2BodyUserData bodyUserData;
    Contactable* contactable = this;
    bodyUserData.pointer = reinterpret_cast<uintptr_t>(contactable);
    bodyDef.userData = bodyUserData;

    mBody = mWorld.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(width / 2.0f, height / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.isSensor = true;

    mBody->CreateFixture(&fixtureDef);
}

Tape::~Tape() {
    mWorld.DestroyBody(mBody);
}

void Tape::update() {}

void Tape::draw(Graphics& g) {
    g.push();

    g.fill(mColor);

    g.rectMode(DrawMode::CENTER);
    g.noStroke();
    g.rect(mPosition.x, mPosition.y, mWidth, mHeight);

    g.pop();
}
