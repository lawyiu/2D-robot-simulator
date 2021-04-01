#include "robot.hpp"

#include "led.hpp"

#include <dlfcn.h>
#include <iostream>

#define DEFAULT_LIB "./libcode.so"

using namespace piksel;
using namespace std;

Robot::~Robot() {
    unloadCode();
}

void Robot::init() {
    unique_ptr<Output> ledPtr(new Led(*this));
    mOutputs.push_back(move(ledPtr));

    loadCode();

    if (mSetup) {
        mSetup();
    }
}

void Robot::loadCode() {
    char* error;

    mLibHandle = dlopen(DEFAULT_LIB, RTLD_NOW);
    if (!mLibHandle) {
        cerr << "[Robot] Error loading the Arduino code from library: " << dlerror() << endl;
    } else {
        dlerror(); // Clear any existing error
        mSetup = reinterpret_cast<setup_t>(dlsym(mLibHandle, "setup"));

        if ((error = dlerror())) {
            cerr << "[Robot] Could not find setup function: " << error << endl;
        }

        dlerror(); // Clear any existing error
        mLoop = reinterpret_cast<loop_t>(dlsym(mLibHandle, "loop"));

        if ((error = dlerror())) {
            cerr << "[Robot] Could not find loop function: " << error << endl;
        }
    }
}

void Robot::unloadCode() {
    if (mLibHandle) {
        if (dlclose(mLibHandle)) {
            cerr << "[Robot] Could not close the library: " << dlerror() << endl;
        }
    }
}

void Robot::reloadCode() {
    unloadCode();
    loadCode();

    if (mSetup) {
        mSetup();
    }
}

void Robot::update() {
    if (mLoop) {
        mLoop();
    }

    for (auto&& output : mOutputs) {
        output->update();
    }
}

void Robot::draw(Graphics& g) {
    g.push();

    g.fill(mColor);
    g.rectMode(DrawMode::CENTER);
    g.rotate(mRotation * PI / 180.0f);
    g.translate(mPosition.x, mPosition.y);
    g.noStroke();
    g.rect(0.0f, 0.0f, mWidth, mHeight);

    for (auto&& output : mOutputs) {
        output->draw(g);
    }

    g.pop();
}
