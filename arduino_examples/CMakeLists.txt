cmake_minimum_required(VERSION 3.12)
project(Arduino_Examples)
set(CMAKE_CXX_STANDARD 11)

if(EMSCRIPTEN)
    set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
    # Remove "-shared" from link command to allow "-s SIDE_MODULE=1" to take effect.
    string(REPLACE "-shared" "" CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS ${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS})
endif()

aux_source_directory(. SOURCES)

foreach(SRC_FILE ${SOURCES})
    get_filename_component(BASE_FILENAME ${SRC_FILE} NAME_WE)
    add_library(${BASE_FILENAME} MODULE ${SRC_FILE})

    if(EMSCRIPTEN)
        target_compile_options(${BASE_FILENAME} PRIVATE -s SIDE_MODULE=1)
        set_target_properties(${BASE_FILENAME} PROPERTIES LINK_FLAGS "-s SIDE_MODULE=1 -s EXPORTED_FUNCTIONS=['_setup','_loop']")
    endif()

    target_include_directories(${BASE_FILENAME} PUBLIC ${2D_Robot_Sim_SOURCE_DIR}/src)
    set_target_properties(${BASE_FILENAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
endforeach()
