#ifndef APP_HPP
#define APP_HPP

#include "robot.hpp"
#include <piksel/baseapp.hpp>

#define INIT_SCALE_FACTOR 10.0f

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(640, 480) {}
    void setup();
    void draw(piksel::Graphics& g);

    void keyPressed(int key);
    void mouseWheel(int delta);

private:
    float mScaleFactor = INIT_SCALE_FACTOR; // Pixels per cm
    float mWheelFactor = 100.0f;            // Controls mouse wheel speed
    Robot mRobot;
};
#endif /* APP_HPP */
