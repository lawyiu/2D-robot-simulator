#include "tire.hpp"

#include "app.hpp"
#include "robot.hpp"

Tire::Tire(Robot& robot, glm::vec2 position, float width, float height, glm::vec4 color, Side side)
    : mRobot(robot), mWidth(width), mHeight(height), mColor(color), mWorld(App::getInstance().getWorld()), mSide(side) {
    createBody(position);
    createJoint(position);
}

Tire::~Tire() {
    mWorld.DestroyJoint(mWeldJoint);
    mWorld.DestroyBody(mTireBody);
}

void Tire::createBody(glm::vec2 position) {
    glm::vec2 robotPosition = mRobot.getPosition();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(robotPosition.x + position.x, robotPosition.y + position.y);
    mTireBody = mWorld.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(mWidth / 2.0f, mHeight / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.8f;

    mTireBody->CreateFixture(&fixtureDef);

    App::getInstance().getCurrentLevel().createFrictionJoint(mTireBody);
}

void Tire::createJoint(glm::vec2 position) {
    // Attach to robot body
    b2Body* robotBody = mRobot.getBody();
    b2WeldJointDef weldJointDef;
    weldJointDef.Initialize(mTireBody, robotBody, mTireBody->GetPosition());
    weldJointDef.collideConnected = false;

    mWeldJoint = mWorld.CreateJoint(&weldJointDef);
}

void Tire::draw(piksel::Graphics& g) {
    g.push();

    b2Vec2 pos = mTireBody->GetPosition();

    g.translate(pos.x, pos.y);
    g.rotate(mTireBody->GetAngle());

    g.fill(mColor);
    g.rect(0.0f, 0.0f, mWidth, mHeight);

    g.pop();
}

glm::vec2 Tire::getHeading() {
    b2Vec2 heading = mTireBody->GetWorldVector(b2Vec2(1.0f, 0.0f));
    return glm::vec2(heading.x, heading.y);
}

b2Vec2 Tire::getForwardVelocity() {
    b2Vec2 normalVec = mTireBody->GetWorldVector(b2Vec2(1.0f, 0.0f));
    return b2Dot(mTireBody->GetLinearVelocity(), normalVec) * normalVec;
}

void Tire::applyForce(float force) {
    glm::vec2 forceVec(getHeading() * force);
    float velocity = getForwardVelocity().Length();
    if (velocity < mMaxVelocity) {
        mTireBody->ApplyForceToCenter(b2Vec2(forceVec.x, forceVec.y), true);
    }
}
