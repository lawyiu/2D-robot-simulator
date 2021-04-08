cmake_minimum_required(VERSION 3.12)
project(2D_Robot_Sim)
set(CMAKE_CXX_STANDARD 11)

if(EMSCRIPTEN)
    string(PREPEND CMAKE_CXX_FLAGS "-fpic ")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(googletest
                 EXCLUDE_FROM_ALL)

add_subdirectory(arduino_examples)

add_subdirectory(lib/piksel)

if(EMSCRIPTEN)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/preRun.js ${CMAKE_BINARY_DIR}/preRun.js COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html ${CMAKE_BINARY_DIR}/shell.html COPYONLY)
endif()

set(SOURCES
    src/Arduino.cpp
    src/robot.cpp
    src/pinsController.cpp
    src/led.cpp
    src/main.cpp
    src/app.cpp
)
add_executable(index ${SOURCES})

if(EMSCRIPTEN)
    target_compile_options(index PRIVATE -s MAIN_MODULE=1)
    set_target_properties(index PROPERTIES LINK_FLAGS "-s MAIN_MODULE=1 --pre-js preRun.js")
else()
    set_target_properties(index PROPERTIES LINK_FLAGS "-Wl,--dynamic-list=\"${PROJECT_SOURCE_DIR}\"/syms.txt")
endif()

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

add_dependencies(tests piksel)
