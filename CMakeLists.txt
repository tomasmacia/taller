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
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# source files
set(SOURCE_FILES
        # parser module
        src/parser/xmlparser.cpp
        src/parser/xmlparser.h
        src/parser/CLIArgumentParser.cpp
        src/parser/CLIArgumentParser.h
        src/parser/config/config.h
        src/parser/config/bindings.h
        src/parser/config/gameplay.h
        src/parser/config/characterxml.h
        src/parser/config/level.h
        src/parser/config/weapons.h
        src/parser/config/utilities.h
        src/parser/config/npc.h
        src/parser/config/screenresolution.h
        src/parser/config/utility.h
        src/parser/config/weapon.h
        src/parser/credentials/Credentials.h
        src/parser/credentials/UserCredentials.h

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

        # utils
        src/utils/TimeUtils.cpp
        src/utils/TimeUtils.h

        #main
        src/game/main.cpp

        # game
        src/game/LoggerMenu.cpp
        src/game/LoggerMenu.h
        src/game/Game.h
        src/game/Game.cpp
        src/game/GameServer.h
        src/game/GameServer.cpp
        src/game/GameClient.h
        src/game/GameClient.cpp
        src/game/Controller.cpp
        src/game/Controller.h
        src/game/ECS.h
        src/game/Manager.h
        src/game/Manager.cpp
        src/game/Action.h
        src/game/LevelBuilder.h
        src/game/LevelBuilder.cpp
        src/game/PositionComponent.h 
        src/game/PositionComponent.cpp
        src/game/CameraComponent.cpp 
        src/game/CameraComponent.h 
        src/game/TextureWrapper.cpp 
        src/game/TextureWrapper.h 
        src/game/PhysicsComponent.cpp 
        src/game/PhysicsComponent.h 
        src/game/StateComponent.cpp 
        src/game/StateComponent.h 
        src/game/InputComponent.cpp 
        src/game/InputComponent.h
        src/game/IAComponent.h  
        src/game/IAComponent.cpp
        src/game/RenderComponent.h
        src/game/RenderComponent.cpp
        src/game/CharacterRenderComponent.h
        src/game/CharacterRenderComponent.cpp 
        src/game/NPCRenderComponent.h
        src/game/NPCRenderComponent.cpp   
        src/game/BackgroundRenderComponent.h
        src/game/BackgroundRenderComponent.cpp       
        src/game/MobileRenderComponent.cpp
        src/game/MobileRenderComponent.h
        src/game/NonMobileRenderComponent.cpp
        src/game/NonMobileRenderComponent.h 
        src/game/LevelLimits.h
        src/game/LevelLimits.cpp

        src/game/ToClientPack.h
        src/game/ToClientPack.cpp
        src/game/IDPlayer.cpp 
        src/game/IDPlayer.h 
        src/game/IDComponent.cpp 
        src/game/IDComponent.h
        src/game/LoggerMenu.cpp
        src/game/LoggerMenu.h
        src/game/ObjectSerializer.cpp
        src/game/ObjectSerializer.h
        src/game/MessageParser.cpp
        src/game/MessageParser.h
        src/game/MessageId.h

        # net
        src/net/Client.cpp
        src/net/Client.h
        src/net/Server.cpp
        src/net/Server.h
        src/net/UserConnection.cpp 
        src/net/UserConnection.h
        src/utils/ImageUtils.cpp src/utils/ImageUtils.h)

# create executable
add_executable(game ${SOURCE_FILES})

# link libraries
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${XMLPARSER})
