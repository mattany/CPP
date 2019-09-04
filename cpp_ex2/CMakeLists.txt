#cmake_minimum_required(VERSION 3.12)
#project(cpp_ex2)
#
#set(CMAKE_CXX_STANDARD 14)
#
#add_executable(cpp_ex2 main.cpp Fractal.cpp Fractal.h)
cmake_minimum_required(VERSION 3.12)
project(cpp_ex2)

include_directories(/cs/usr/mattan/Desktop/CPP/cpp_ex2/lib/pkgconfig)

find_library(ex1_lib cpp_ex2)

#grouping the libraries
set(frameworks ${ex1_lib})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES ex2_cpp_tester_v0.1.cpp)

add_executable(cpp_ex2 main.cpp ex2_cpp_tester_v0.1.cpp)

target_link_libraries(cpp_ex2 gtest gtest_main)