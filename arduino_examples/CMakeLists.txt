cmake_minimum_required(VERSION 3.12)
project(Arduino_Examples)
set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. SOURCES)

foreach(SRC_FILE ${SOURCES})
    get_filename_component(BASE_FILENAME ${SRC_FILE} NAME_WE)
    add_library(${BASE_FILENAME} MODULE ${SRC_FILE})
    target_include_directories(${BASE_FILENAME} PUBLIC ${2D_Robot_Sim_SOURCE_DIR}/src)
    set_target_properties(${BASE_FILENAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
endforeach()
