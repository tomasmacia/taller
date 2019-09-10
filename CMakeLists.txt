cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(src/parser)
link_directories(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(game
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
        src/parser/config/utility.h
        src/main.cpp src/parser/config/weapon.h)

target_link_libraries(game tinyxml2)