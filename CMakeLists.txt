cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(src/parser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(game
        src/parser/tinyxml2.cpp
        src/parser/tinyxml2.h
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
        src/parser/config/barrels.h
        src/parser/config/boxes.h
        src/main.cpp)
