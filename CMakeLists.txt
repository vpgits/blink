cmake_minimum_required(VERSION 3.28)
project(blink)

set(CMAKE_CXX_STANDARD 26)

find_package(raylib REQUIRED)

add_executable(blink src/main.cpp
)

target_link_libraries(blink raylib)
