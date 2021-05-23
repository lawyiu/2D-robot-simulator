#include "tire.hpp"

#include "app.hpp"
#include "robot.hpp"

Tire::Tire(Robot& robot, glm::vec2 position, float width, float height, glm::vec4 color, Side side)
    : mRobot(robot), mWidth(width), mHeight(height), mColor(color), mWorld(App::getInstance().getWorld()), mSide(side) {

    createBody(position);
    createJoint();
}

Tire::~Tire() {
    mWorld.DestroyJoint(mDistJoint);
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
}

void Tire::createJoint() {
    // Attach to robot body
    b2Body* robotBody = mRobot.getBody();
    b2DistanceJointDef distJointDef;
    // For simplicity, connect the tire to the center of the robot for now.
    distJointDef.Initialize(mTireBody, robotBody, mTireBody->GetPosition(), robotBody->GetPosition());
    distJointDef.collideConnected = false;

    mDistJoint = static_cast<b2DistanceJoint*>(mWorld.CreateJoint(&distJointDef));
}

void Tire::draw(piksel::Graphics& g) {
    g.push();

    float axelWidth = 0.01f;
    float axelHeight = 0.02f;

    b2Vec2 position = mTireBody->GetPosition();

    g.rotate(mTireBody->GetAngle());
    g.translate(position.x, position.y);

    g.fill(mColor);
    g.rect(0.0f, 0.0f, mWidth, mHeight);

    g.pop();
}
