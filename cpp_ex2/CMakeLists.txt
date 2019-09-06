cmake_minimum_required(VERSION 3.14)
project(cpp_ex2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cpp_ex2
        CMakeLists.txt
        Fractal.cpp
        Fractal.h
        main.cpp)
