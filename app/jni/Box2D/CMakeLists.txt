
cmake_minimum_required(VERSION 3.8)

# https://cmake.org/cmake/help/latest/command/project.html
project(Box2D VERSION 2.4.0)

set(BOX2D_SOURCE_FILES
        src/Box2D.h)


##### library generation #####
add_library(Box2D Box2D.h)
target_include_directories(Box2D PUBLIC ${BOX2D_SOURCE_FILES})
