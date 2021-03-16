#ifndef APP_HPP
#define APP_HPP

#include "robot.hpp"
#include <piksel/baseapp.hpp>

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(640, 480) {}
    void setup();
    void draw(piksel::Graphics& g);

    void mouseWheel(int delta);

private:
    float mScaleFactor = 10.0f;  // Pixels per cm
    float mWheelFactor = 100.0f; // Controls mouse wheel speed
    Robot* mRobot;
};
#endif /* APP_HPP */
