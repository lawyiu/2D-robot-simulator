#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "output.hpp"
#include "pinsController.hpp"

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <graphics.hpp>
#include <memory>

typedef void (*setup_t)(void);
typedef void (*loop_t)(void);

class Robot {
public:
    Robot(b2World* world) : Robot(world, glm::vec2(0.0f, 0.0f), 0.0f, 0.30f, 0.15f, glm::vec4(0.8f, 0.4f, 0.0f, 1.0f)) {}

    /* Rotation angle in radians.
       Width and height in meters. */
    Robot(b2World* world, glm::vec2 position, float rotation, float width, float height, glm::vec4 color)
        : mWorld(world), mPosition(position), mRotation(rotation), mWidth(width), mHeight(height), mColor(color),
          mPins(20) {}
    ~Robot();

    /* For vector of unique_ptr member. Helps with debugging compiler errors.*/
    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    void init();
    void loadCode();
    void unloadCode();
    void reloadCode();
    void update();
    void draw(piksel::Graphics& g);

    float getRotation() { return mBody->GetAngle(); }
    void setRotation(float radians) { mBody->SetTransform(mBody->GetPosition(), radians); }
    glm::vec2 getHeading();
    void setHeading(glm::vec2 heading);
    glm::vec2 getLeftPerpendicularVec();
    glm::vec2 getRightPerpendicularVec();

    glm::vec2 getPosition();
    PinsController& getPinsController() { return mPins; }

private:
    glm::vec2 mPosition;
    float mWidth;
    float mHeight;
    float mRotation;
    glm::vec4 mColor;

    b2World* mWorld;
    b2Body* mBody;

    PinsController mPins;
    std::vector<std::unique_ptr<Output>> mOutputs;

    void* mLibHandle = nullptr;
    setup_t mSetup = nullptr;
    loop_t mLoop = nullptr;
};

#endif /* ROBOT_HPP */
