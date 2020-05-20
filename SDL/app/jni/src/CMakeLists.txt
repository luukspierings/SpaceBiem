cmake_minimum_required(VERSION 3.6)

project(MY_APP)

find_library(SDL2 SDL2)
find_library(SDL2_ttf SDL2_ttf)
find_library(SDL2_mixer SDL2_mixer)
find_library(SDL2_image SDL2_image)
find_library(Box2D Box2D)

add_library(main SHARED)

target_sources(main PRIVATE main.cpp)

target_link_libraries(main SDL2)
target_link_libraries(main SDL2_ttf)
target_link_libraries(main SDL2_mixer)
target_link_libraries(main SDL2_image)
target_link_libraries(main Box2D)


