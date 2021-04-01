#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "output.hpp"
#include "pinsController.hpp"

#include <glm/glm.hpp>
#include <graphics.hpp>
#include <memory>

typedef void (*setup_t)(void);
typedef void (*loop_t)(void);

class Robot {
public:
    Robot() : Robot(glm::vec2(0.0f, 0.0f), 0.0f, 10.0f, 5.0f, glm::vec4(0.8f, 0.4f, 0.0f, 1.0f)) {}

    /* Rotation angle in degrees.
       Width and height in cm. */
    Robot(glm::vec2 position, float rotation, float width, float height, glm::vec4 color)
        : mPosition(position), mRotation(rotation), mWidth(width), mHeight(height), mColor(color), mPins(20) {}
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

    PinsController& getPinsController() { return mPins; }

private:
    glm::vec2 mPosition;
    float mWidth;
    float mHeight;
    float mRotation;
    glm::vec4 mColor;

    PinsController mPins;
    std::vector<std::unique_ptr<Output>> mOutputs;

    void* mLibHandle = nullptr;
    setup_t mSetup = nullptr;
    loop_t mLoop = nullptr;
};

#endif /* ROBOT_HPP */
