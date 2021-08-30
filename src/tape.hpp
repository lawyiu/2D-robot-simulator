#ifndef TAPE_HPP
#define TAPE_HPP

#include "contactable.hpp"

#include <graphics.hpp>
#include <glm/glm.hpp>

class b2World;
class b2Body;

class Tape : public Contactable {
public:
    // Position, width, and height in meters
    // Angle in rads
    Tape(b2World& world, glm::vec2 position, float angle, float width, float height)
        : Tape(world, position, angle, glm::vec4(0.43f, 0.45f, 0.44f, 1.0f), width, height) {}

    Tape(b2World& world, glm::vec2 position, float width, float height)
        : Tape(world, position, 0.0f, glm::vec4(0.43f, 0.45f, 0.44f, 1.0f), width, height) {}

    Tape(b2World& world, glm::vec2 position, float angle, glm::vec4 color, float width, float height);

    ~Tape();

    void update();
    void draw(piksel::Graphics& g);

    void contactBegin(Contactable& other) override {}
    void contactEnd(Contactable& other) override {}

private:
    glm::vec2 mPosition;
    glm::vec4 mColor;
    float mWidth;
    float mHeight;
    b2World& mWorld;
    b2Body* mBody;
};

#endif /* TAPE_HPP */
