cmake_minimum_required(VERSION 3.6)
project(BMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp BooleanMatrix.cpp BooleanMatrix.h)
add_executable(BMM ${SOURCE_FILES})