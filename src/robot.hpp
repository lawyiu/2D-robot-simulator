#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "input.hpp"
#include "output.hpp"
#include "pinsController.hpp"
#include "tire.hpp"

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <graphics.hpp>
#include <memory>

typedef void (*setup_t)(void);
typedef void (*loop_t)(void);

#define DEF_WIDTH 0.30f
#define DEF_HEIGHT 0.15f
#define DEF_COLOR glm::vec4(0.8f, 0.4f, 0.0f, 0.7f)

class Robot {
public:
    Robot(b2World* world) : Robot(world, glm::vec2(0.0f, 0.0f), 0.0f, DEF_WIDTH, DEF_HEIGHT, DEF_COLOR) {}

    /* Position in meters.
       Rotation angle in radians. */
    Robot(b2World* world, glm::vec2 position, float rotation)
        : Robot(world, position, rotation, DEF_WIDTH, DEF_HEIGHT, DEF_COLOR) {}

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

    b2Body* getBody() { return mBody; }
    b2World* getWorld() { return mWorld; }

    /* Applies force to the left or right tires to make the robot move. */
    void applyForce(float force, Tire::Side);

protected:
    void createBody();
    void addTires();

    glm::vec2 mPosition;
    float mWidth;
    float mHeight;
    float mRotation;
    glm::vec4 mColor;

    b2World* mWorld;
    b2Body* mBody;

    PinsController mPins;
    std::vector<std::unique_ptr<Input>> mInputs;
    std::vector<std::unique_ptr<Output>> mOutputs;
    std::vector<std::unique_ptr<Tire>> mTires;

    void* mLibHandle = nullptr;
    setup_t mSetup = nullptr;
    loop_t mLoop = nullptr;
};

#endif /* ROBOT_HPP */
