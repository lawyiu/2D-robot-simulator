#include "tape.hpp"

#include <box2d/box2d.h>

using namespace piksel;

Tape::Tape(b2World& world, glm::vec2 position, float angle, glm::vec4 color, float width, float height)
    : mWorld(world), mPosition(position), mColor(color), mWidth(width), mHeight(height) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(mPosition.x, mPosition.y);
    bodyDef.angle = angle;

    b2BodyUserData bodyUserData;
    Contactable* contactable = this;
    bodyUserData.pointer = reinterpret_cast<uintptr_t>(contactable);
    bodyDef.userData = bodyUserData;

    mBody = mWorld.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width / 2.0f, height / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
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

    b2Vec2 tapePos = mBody->GetPosition();
    g.translate(tapePos.x, tapePos.y);
    g.rotate(mBody->GetAngle());

    // Overdraw by 0.01f to account for box2D "skin" thinkness
    g.rect(0.0f, 0.0f, mWidth + 0.01f, mHeight + 0.01f);

    g.pop();
}
