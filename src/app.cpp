#include "app.hpp"
#include "robot.hpp"

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

    mLevel.reset(new Level());
    mLevel->init();
}

void App::update() {
    updateDeltaTime();
    float dt = getDeltaTimeSeconds();

    if (mReload) {
        getCurrentRobot().reloadCode();
        mReload = false;
    } else if (mRestart) {
        mLevel.reset(new Level());
        mLevel->init();
        mRestart = false;
    }

    if (!mPause) {
        mLevel->update();
    }

    float keyPanDist = pixelsPerSecond * dt;

    if (mFollow) {
        glm::vec2 position = getCurrentRobot().getPosition();

        mOffsetX = -position.x * mScaleFactor;
        mOffsetY = -position.y * mScaleFactor;
    } else {
        if (mKeyPanState & PAN_UP) {
            mOffsetY -= keyPanDist;
        }
        if (mKeyPanState & PAN_DOWN) {
            mOffsetY += keyPanDist;
        }
        if (mKeyPanState & PAN_LEFT) {
            mOffsetX -= keyPanDist;
        }
        if (mKeyPanState & PAN_RIGHT) {
            mOffsetX += keyPanDist;
        }
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

    if (mFollow) {
        g.textFont(mFont);
        g.textSize(mTextSize);
        g.text("Following", mTextPadding, mTextSize);
    }

    g.translate(width / 2.0f + mOffsetX, height / 2.0f + mOffsetY);
    g.scale(mScaleFactor, mScaleFactor);

    mLevel->draw(g);
}

Robot& App::getCurrentRobot() {
    return mLevel->getRobot();
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

        case GLFW_KEY_F:
            mFollow = !mFollow;
            break;

        case GLFW_KEY_UP:
            mKeyPanState |= PAN_UP;
            break;

        case GLFW_KEY_DOWN:
            mKeyPanState |= PAN_DOWN;
            break;

        case GLFW_KEY_LEFT:
            mKeyPanState |= PAN_LEFT;
            break;

        case GLFW_KEY_RIGHT:
            mKeyPanState |= PAN_RIGHT;
            break;

        default:
            break;
    }
}

void App::keyReleased(int key) {
    switch (key) {
        case GLFW_KEY_UP:
            mKeyPanState &= ~PAN_UP;
            break;

        case GLFW_KEY_DOWN:
            mKeyPanState &= ~PAN_DOWN;
            break;

        case GLFW_KEY_LEFT:
            mKeyPanState &= ~PAN_LEFT;
            break;

        case GLFW_KEY_RIGHT:
            mKeyPanState &= ~PAN_RIGHT;
            break;

        default:
            break;
    }
}

void App::mouseWheel(int delta) {
    float dt = getDeltaTimeSeconds();
    mScaleFactor += delta / mWheelFactor * dt;

    /* Clamp scale factor to avoid objects becoming bigger when zooming out too much. */
    if (mScaleFactor < 0.5) {
        mScaleFactor = 0.5;
    }
}

void App::mouseMoved(int x, int y) {
    float dt = getDeltaTimeSeconds();

    switch (mMousePanState) {
        case START_PAN:
            mOrigX = x;
            mOrigY = y;

            mMousePanState = PANNING;
            break;

        case PANNING:
            mOffsetX += (x - mOrigX);
            mOffsetY += (y - mOrigY);
            mOrigX = x;
            mOrigY = y;
            break;

        default:
            break;
    }
}

void App::mousePressed(int button) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mMousePanState = START_PAN;
            break;

        default:
            break;
    }
}

void App::mouseReleased(int button) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mMousePanState = NO_PAN;
            break;

        default:
            break;
    }
}
