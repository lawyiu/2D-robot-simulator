cmake_minimum_required(VERSION 3.12)
project(2D_Robot_Sim)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if(EMSCRIPTEN)
    string(PREPEND CMAKE_CXX_FLAGS "-fpic ")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(googletest
                 EXCLUDE_FROM_ALL)

if(EMSCRIPTEN)
    set(BOX2D_BUILD_UNIT_TESTS OFF)
endif()

set(BOX2D_BUILD_TESTBED OFF)
add_subdirectory(box2d)

add_subdirectory(arduino_examples)

add_subdirectory(lib/piksel)

if(EMSCRIPTEN)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/preRun.js ${CMAKE_BINARY_DIR}/preRun.js COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/postRun.js ${CMAKE_BINARY_DIR}/postRun.js COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/editor.js ${CMAKE_BINARY_DIR}/editor.js COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/compile.js ${CMAKE_BINARY_DIR}/compile.js COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html ${CMAKE_BINARY_DIR}/shell.html COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/shell.css ${CMAKE_BINARY_DIR}/shell.css COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/index.css ${CMAKE_BINARY_DIR}/index.css COPYONLY)
endif()

set(SOURCES
    src/Arduino.cpp
    src/robot.cpp
    src/tire.cpp
    src/pinsController.cpp
    src/led.cpp
    src/main.cpp
    src/app.cpp
)
add_executable(sim ${SOURCES})

if(EMSCRIPTEN)
    add_custom_command(
        TARGET sim PRE_BUILD
        COMMAND $ENV{EMSDK}/upstream/emscripten/tools/file_packager code --preload arduino_examples/libwelcome.so@/libcode.so --js-output=code.js
        VERBATIM)
    add_dependencies(sim welcome)
    target_compile_options(sim PRIVATE -s MAIN_MODULE=1)
    set_target_properties(sim PROPERTIES LINK_FLAGS "-s MAIN_MODULE=1 --pre-js preRun.js --post-js postRun.js --extern-pre-js code.js")
else()
    set_target_properties(sim PROPERTIES LINK_FLAGS "-Wl,--dynamic-list=\"${PROJECT_SOURCE_DIR}\"/syms.txt")
endif()

target_include_directories(sim
    PUBLIC src
    PUBLIC lib/piksel/src
    PUBLIC box2d/include/box2d
)
target_link_libraries(sim
    piksel
    box2d
)

if(EMSCRIPTEN)
    set(DEPLOY_FILES
        index.html
        shell.css
        index.css
        editor.js
        compile.js
        sim.html
        sim.js
        sim.wasm
        sim.data
        code
    )

    set(DEPLOY_EXAMPLES
        examples.json
        welcome.ino
        hello.ino
        blink_no_delay.ino
    )
    list(TRANSFORM DEPLOY_EXAMPLES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/arduino_examples/)

    add_custom_target(deploy
        DEPENDS sim
        COMMAND_EXPAND_LISTS
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/deploy
        COMMAND ${CMAKE_COMMAND} -E copy ${DEPLOY_FILES} ${CMAKE_BINARY_DIR}/deploy
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/deploy/examples
        COMMAND ${CMAKE_COMMAND} -E copy ${DEPLOY_EXAMPLES} ${CMAKE_BINARY_DIR}/deploy/examples
        VERBATIM
    )
endif()

if(NOT EMSCRIPTEN)
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
endif()
