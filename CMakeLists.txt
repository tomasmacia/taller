# CMake version
cmake_minimum_required(VERSION 3.0)

# project name
project(taller)

# flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# includes
include_directories(./include ./src)

# binary output
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp
src/Logger.h
src/Logger.cpp)

add_executable(game ${SOURCE_FILES})

target_link_libraries(game ${SDL2_LIBRARY})