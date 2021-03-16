#include "app.hpp"

void App::setup() {
    mRobot = new Robot();
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.5f, 0.7f, 0.5f, 1.0f));
    g.translate(width / 2.0f, height / 2.0f);
    g.scale(mScaleFactor, mScaleFactor);

    mRobot->draw(g);
}
