#include "app.hpp"

#include <limits.h>

App& App::getInstance() {
    static App app;
    return app;
}

void App::updateDeltaTime() {
    int newMillis = millis();
    mDeltaTimeMillis = newMillis - mPrevMillis;

    // Handle overflow
    if (mDeltaTimeMillis < 0) {
        int leftOver = std::numeric_limits<int>::max() - mPrevMillis;
        mDeltaTimeMillis = newMillis + leftOver;
    }

    mPrevMillis = newMillis;
}

void App::setup() {
    mFont.load("data/fonts/OpenSans/OpenSans-Regular.ttf");

    mRobot.reset(new Robot());
    mRobot->init();
}

void App::update() {
    updateDeltaTime();
    float dt = getDeltaTimeSeconds();

    if (mReload) {
        mRobot->reloadCode();
        mReload = false;
    } else if (mRestart) {
        mRobot.reset(new Robot());
        mRobot->init();
        mRestart = false;
    }

    if (!mPause) {
        mRobot->update();
    }

    float keyPanDist = pixelsPerSecond * dt;
    switch (mKeyPanState) {
        case PAN_UP:
            mOffsetY -= keyPanDist;
            break;

        case PAN_DOWN:
            mOffsetY += keyPanDist;
            break;

        case PAN_LEFT:
            mOffsetX -= keyPanDist;
            break;

        case PAN_RIGHT:
            mOffsetX += keyPanDist;
            break;

        default:
            break;
    }
}

void App::draw(piksel::Graphics& g) {
    update();

    g.background(glm::vec4(0.5f, 0.7f, 0.5f, 1.0f));

    if (mPause) {
        g.textFont(mFont);
        g.textSize(mTextSize);
        g.text("Paused", mTextPadding, height - mTextPadding);
    }

    g.translate(width / 2.0f + mOffsetX, height / 2.0f + mOffsetY);
    g.scale(mScaleFactor, mScaleFactor);

    mRobot->draw(g);
}

Robot& App::getCurrentRobot() {
    return *mRobot;
}

void App::keyPressed(int key) {
    switch (key) {
        case GLFW_KEY_0:
            mScaleFactor = INIT_SCALE_FACTOR;
            break;

        case GLFW_KEY_SPACE:
            mPause = !mPause;
            break;

        case GLFW_KEY_L:
            mReload = true;
            break;

        case GLFW_KEY_R:
            mRestart = true;
            break;

        case GLFW_KEY_UP:
            mKeyPanState = PAN_UP;
            break;

        case GLFW_KEY_DOWN:
            mKeyPanState = PAN_DOWN;
            break;

        case GLFW_KEY_LEFT:
            mKeyPanState = PAN_LEFT;
            break;

        case GLFW_KEY_RIGHT:
            mKeyPanState = PAN_RIGHT;
            break;

        default:
            break;
    }
}

void App::keyReleased(int key) {
    switch (key) {
        case GLFW_KEY_UP:
        case GLFW_KEY_DOWN:
        case GLFW_KEY_LEFT:
        case GLFW_KEY_RIGHT:
            mKeyPanState = PAN_NONE;
            break;

        default:
            break;
    }
}

void App::mouseWheel(int delta) {
    mScaleFactor += delta / mWheelFactor;

    /* Clamp scale factor to avoid objects becoming bigger when zooming out too much. */
    if (mScaleFactor < 0.5) {
        mScaleFactor = 0.5;
    }
}
