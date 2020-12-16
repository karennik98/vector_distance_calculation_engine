cmake_minimum_required(VERSION 3.17)

project(vector_distance_calculation_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/)
file(GLOB SRCS_PATH  ${SRC_PATH}*.cpp)

set(EXECS ${SRC_PATH}/main.cpp)

add_library(${PROJECT_NAME} ${SRCS_PATH})

FOREACH(exec_src ${EXECS})
    get_filename_component(exec_name ${exec_src} NAME_WE)
    add_executable(${exec_name} ${exec_src} src/settings.cpp include/settings.hpp)
    target_link_libraries(${exec_name} ${PROJECT_NAME})
ENDFOREACH()
