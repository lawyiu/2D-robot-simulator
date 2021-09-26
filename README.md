# 2D-robot-simulator
[![CircleCI](https://circleci.com/gh/lawyiu/2D-robot-simulator/tree/main.svg?style=shield)](https://circleci.com/gh/lawyiu/2D-robot-simulator/tree/main)
[![Azure Static Web Apps CI/CD](https://github.com/lawyiu/2D-robot-simulator/actions/workflows/azure-static-web-apps-agreeable-ocean-0a407871e.yml/badge.svg?branch=main)](https://github.com/lawyiu/2D-robot-simulator/actions/workflows/azure-static-web-apps-agreeable-ocean-0a407871e.yml)

A 2 dimensional top down robot simulator designed to allow users to run their Arduino code on a virtual robot.

Try out the [web demo](https://lawyiu.github.io/2D-robot-simulator/)!

## Building instructions (Windows (WSL), macOS, Linux)
Please note that Windows users will need to use WSL to build for the web or desktop.

### Common Setup
  1. `git clone --recursive https://github.com/lawyiu/2D-robot-simulator.git`

  2. `cd 2D-robot-simulator`

### Web
  3. Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)

  4. `mkdir build_web`

  5. `cd build_web`

  6. `emcmake cmake ../`

  7. `make deploy`

  8. `cd deploy`

  9. `emrun --no_browser --port=8080 index.html`

  10. Open a browser and go to http://localhost:8080

### Desktop
  3. `mkdir build`

  4. `cd build`

  5. `cmake ../`

  6. `make`

  7. `ln -sf arduino_examples/libhello.so libcode.so`
     To run different programs, replace `libhello.so` in the command with the name of the compiled program you want to
     run.

  8. `./sim`
     To run custom programs, place the ino file inside the arduino_examples folder. Add the ino file to the INO_SOURCES list
     in `arduino_examples/CMakeLists.txt`. Then run `make` and redo step 7 with the name of your custom compiled program.

## Controls
### Keys
    R - Restart the simulation.
    L - Load new code without restarting the simulation.
    Spacebar - Pause the simulation.
    Arrow Keys / left mouse button - Pan the camera around.
    Mouse wheel - Zoom in or out.
    F - Follow the robot with the camera.

## What's working
  * Serial printing
  * Setting pinmode
  * Digital/analog read and write
  * `millis()`
  * `randomSeed()` and `random()`

## Limitations of the Simulator
  * Serial reading is not supported yet.

  * Function prototypes are not automatically generated. Normally, ino sketches do not require the programmer to declare
    function prototypes manually since they are automatically generated during the build process used by the Arduino
    IDE. However, for this project, function prototypes will need to be added manually or the ino sketch might fail to
    compile.

  * Delay functions: `delay()` and `delayMicroseconds()` are not implemented due to the simulator running the Arduino
    program inside the main thread. Thus, any blocking delays will cause the simulator to stop updating/drawing for the
    duration of the delay.

  * Many Arduino API functions and constants are not implemented/defined yet. Check out the header file Arduino.h in the
    src directory to see what is currently implemented/defined.

  * EEPROM is not supported yet.

  * There is not a clear way to use third party Arduino libraries yet.

  * Some Arduino libraries may fail to compile/work if they access the hardware at a lower level than the Arduino API or
    if they use API functions that are not implemented yet.
