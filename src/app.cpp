#include "app.hpp"

App& App::getInstance() {
    static App app;
    return app;
}

void App::setup() {
    mFont.load("data/fonts/OpenSans/OpenSans-Regular.ttf");

    mRobot.reset(new Robot());
    mRobot->init();
}

void App::draw(piksel::Graphics& g) {
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

    g.background(glm::vec4(0.5f, 0.7f, 0.5f, 1.0f));

    if (mPause) {
        g.textFont(mFont);
        g.textSize(mTextSize);
        g.text("Paused", mTextPadding, height - mTextPadding);
    }

    g.translate(width / 2.0f, height / 2.0f);
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
