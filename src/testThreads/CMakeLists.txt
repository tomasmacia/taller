cmake_minimum_required(VERSION 3.15)
project(testThreads)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(testThreads main.cpp A.cpp A.h)