cmake_minimum_required(VERSION 3.10)
project(MTE140_Lab3)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(MTE140_Lab3
        drones_manager.cpp
        drones_manager.hpp
        drones_manager_test.hpp
        lab3_main.cpp)
