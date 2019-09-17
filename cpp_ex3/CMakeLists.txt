cmake_minimum_required(VERSION 3.12)
project(cpp_ex3)

#include_directories(/cs/usr/mattan/Desktop/CPP/cpp_ex3/lib/pkgconfig)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)
#include_directories(lib/googletest-master/googlemock/include)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(SOURCE_FILES cpp_ex3_unit_test.cpp)


add_executable(cpp_ex3 HashMap.hpp HashMapTester1.2.cpp)

#target_link_libraries(cpp_ex3 gtest gtest_main)
