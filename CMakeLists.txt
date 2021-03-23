cmake_minimum_required(VERSION 3.12)
project(2D_Robot_Sim)
set(CMAKE_CXX_STANDARD 11)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(googletest
                 EXCLUDE_FROM_ALL)

add_subdirectory(lib/piksel)

set(SOURCES
    arduino_examples/hello.cpp
    src/Arduino.cpp
    src/robot.cpp
    src/pinsController.cpp
    src/led.cpp
    src/main.cpp
    src/app.cpp
)
add_executable(index ${SOURCES})
target_include_directories(index
    PUBLIC src
    PUBLIC lib/piksel/src
)
target_link_libraries(index
    piksel
)

set(TEST_SOURCES
    src/pinsController.cpp
    tests/pinsControllerTests.cpp
)

add_executable(tests ${TEST_SOURCES})
target_include_directories(tests
    PUBLIC src
)
target_link_libraries(tests gtest_main)
add_test(NAME tests COMMAND tests)
