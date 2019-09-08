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
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})


set(SOURCE_FILES src/main.cpp 
src/LogLib/Logger.h
src/LogLib/Logger.cpp
src/LogLib/ErrorLogger.h
src/LogLib/ErrorLogger.cpp
src/LogLib/InfoLogger.h
src/LogLib/InfoLogger.cpp
src/LogLib/DebugLogger.h
src/LogLib/DebugLogger.cpp
src/LogLib/LogManager.h
src/LogLib/LogManager.cpp
src/window.cpp
src/window.h
src/square.h
src/square.cpp
src/events.h 
src/events.cpp 
src/game.h 
src/game.cpp)

add_executable(game ${SOURCE_FILES})

target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
