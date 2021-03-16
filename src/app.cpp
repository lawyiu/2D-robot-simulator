#include "app.hpp"

void App::setup() {}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.5f, 0.7f, 0.5f, 1.0f));
    g.translate(width / 2.0f, height / 2.0f);
    g.scale(mScaleFactor, mScaleFactor);

    mRobot.draw(g);
}

void App::keyPressed(int key) {
    if (key == GLFW_KEY_0) {
        mScaleFactor = INIT_SCALE_FACTOR;
    }
}

void App::mouseWheel(int delta) {
    mScaleFactor += delta / mWheelFactor;

    /* Clamp scale factor to avoid objects becoming bigger when zooming out too much. */
    if (mScaleFactor < 0.5) {
        mScaleFactor = 0.5;
    }
}
