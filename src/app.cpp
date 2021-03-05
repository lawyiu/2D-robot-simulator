#include "app.hpp"

void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    g.fill(glm::vec4(0.8f, 0.4f, 0.0f, 1.0f));
    g.background(glm::vec4(0.5f, 0.7f, 0.5f, 1.0f));
    g.rect(50, 50, 100, 100);
}
