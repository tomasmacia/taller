cmake_minimum_required(VERSION 3.0)
project(game)

# flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(include)
include_directories(src/parser)
link_directories(lib)

set(XMLPARSER tinyxml2)

IF(APPLE)
    set(XMLPARSER tinyxml2-tomi)
ENDIF(APPLE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# SDL
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# source files
set(SOURCE_FILES
        # parser module
        src/parser/xmlparser.cpp
        src/parser/xmlparser.h
        src/parser/config/config.h
        src/parser/config/bindings.h
        src/parser/config/gameplay.h
        src/parser/config/character.h
        src/parser/config/level.h
        src/parser/config/weapons.h
        src/parser/config/utilities.h
        src/parser/config/npc.h
        src/parser/config/screenresolution.h
        src/parser/config/utility.h
        src/parser/config/weapon.h

        # logger module
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

        # window
        src/window.cpp
        src/window.h
        src/square.cpp
        src/square.h

        #main
        src/main.cpp

        src/events.h 
        src/events.cpp 
        src/game.h 
        src/game.cpp 
        src/character.h 
        src/character.cpp 
        src/background.h 
        src/background.cpp 
        src/object.h 
        src/object.cpp
        src/enemy.h
        src/enemy.cpp
        )

# create executable
add_executable(game ${SOURCE_FILES})

# link libraries
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${XMLPARSER})
