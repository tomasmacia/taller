cmake_minimum_required(VERSION 3.15)
project(testClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(.)

add_executable(testClient
        Client.cpp
        Client.h
        main.cpp Server.cpp Server.h)
