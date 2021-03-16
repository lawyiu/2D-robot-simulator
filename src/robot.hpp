#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <graphics.hpp>

#include <glm/glm.hpp>

class Robot {
public:
    Robot() : Robot(glm::vec2(0.0f, 0.0f), 0.0f, 10.0f, 5.0f, glm::vec4(0.8f, 0.4f, 0.0f, 1.0f)) {}

    /* Rotation angle in degrees.
       Width and height in cm. */
    Robot(glm::vec2 position, float rotation, float width, float height, glm::vec4 color)
        : mPosition(position), mRotation(rotation), mWidth(width), mHeight(height), mColor(color) {}
    void update();
    void draw(piksel::Graphics& g);

private:
    glm::vec2 mPosition;
    float mWidth;
    float mHeight;
    float mRotation;
    glm::vec4 mColor;
};

#endif /* ROBOT_HPP */
