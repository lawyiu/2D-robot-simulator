#ifndef APP_HPP
#define APP_HPP

#include "robot.hpp"
#include <piksel/baseapp.hpp>

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(640, 480) {}
    void setup();
    void draw(piksel::Graphics& g);

private:
    float mScaleFactor = 10.0f; // Pixels per cm
    Robot* mRobot;
};
#endif /* APP_HPP */
