cmake_minimum_required(VERSION 3.0)
project(game)

# flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(include)
include_directories(src/XMLparser)
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
        # XMLparser module
        src/XMLparser/xmlparser.cpp
        src/XMLparser/xmlparser.h
        src/CLIAparser/CLIArgumentParser.cpp
        src/CLIAparser/CLIArgumentParser.h
        src/XMLparser/config/config.h
        src/XMLparser/config/bindings.h
        src/XMLparser/config/gameplay.h
        src/XMLparser/config/characterxml.h
        src/XMLparser/config/level.h
        src/XMLparser/config/weapons.h
        src/XMLparser/config/utilities.h
        src/XMLparser/config/npc.h
        src/XMLparser/config/screenresolution.h
        src/XMLparser/config/utility.h
        src/XMLparser/config/weapon.h
        src/credentials/Credentials.h
        src/credentials/UserCredentials.h

        # logger module
        src/logger/Logger.h
        src/logger/Logger.cpp
        src/logger/ErrorLogger.h
        src/logger/ErrorLogger.cpp
        src/logger/InfoLogger.h
        src/logger/InfoLogger.cpp
        src/logger/DebugLogger.h
        src/logger/DebugLogger.cpp
        src/logger/LogManager.h
        src/logger/LogManager.cpp

        # image
        src/time/TimeUtils.cpp
        src/time/TimeUtils.h
        src/image/ImageUtils.cpp
        src/image/ImageUtils.h

        #main
        src/game/main.cpp

        # game
        src/to_remove_or_modify/LoggerMenu.cpp
        src/to_remove_or_modify/LoggerMenu.h
        src/game/Game.h
        src/game/Game.cpp
        src/game/GameServer.h
        src/game/GameServer.cpp
        src/game/GameClient.h
        src/game/GameClient.cpp
        src/game/Controller.cpp
        src/game/Controller.h
        src/to_remove_or_modify/ECS.h
        src/to_remove_or_modify/Manager.h
        src/to_remove_or_modify/Manager.cpp
        src/enumerates/Action.h
        src/to_remove_or_modify/LevelBuilder.h
        src/to_remove_or_modify/LevelBuilder.cpp
        src/game/Components/PositionComponent.h
        src/game/Components/PositionComponent.cpp
        src/to_remove_or_modify/CameraComponent.cpp
        src/to_remove_or_modify/CameraComponent.h
        src/image/TextureWrapper.cpp
        src/image/TextureWrapper.h
        src/game/Components/PhysicsComponent.cpp
        src/game/Components/PhysicsComponent.h
        src/game/Components/StateComponent.cpp
        src/game/Components/StateComponent.h
        src/game/Components/InputComponent.cpp
        src/game/Components/InputComponent.h
        src/game/Components/IAComponent.h
        src/game/Components/IAComponent.cpp
        src/game/Components/Appearences/RenderComponent.h
        src/game/Components/Appearences/RenderComponent.cpp
        src/game/Components/Appearences/CharacterRenderComponent.h
        src/game/Components/Appearences/CharacterRenderComponent.cpp
        src/game/Components/Appearences/NPCRenderComponent.h
        src/game/Components/Appearences/NPCRenderComponent.cpp
        src/game/Components/Appearences/BackgroundRenderComponent.h
        src/game/Components/Appearences/BackgroundRenderComponent.cpp
        src/game/Components/Appearences/MobileRenderComponent.cpp
        src/game/Components/Appearences/MobileRenderComponent.h
        src/game/Components/Appearences/NonMobileRenderComponent.cpp
        src/game/Components/Appearences/NonMobileRenderComponent.h
        src/to_remove_or_modify/LevelLimits.h
        src/to_remove_or_modify/LevelLimits.cpp
        src/to_remove_or_modify/CharacterLevelLimits.cpp
        src/to_remove_or_modify/CharacterLevelLimits.h
        src/to_remove_or_modify/NonCharacterLevelLimits.cpp
        src/to_remove_or_modify/NonCharacterLevelLimits.h

        src/net/messaging/ToClientPack.h
        src/net/messaging/ToClientPack.cpp
        src/net/messaging/IDPlayer.cpp
        src/net/messaging/IDPlayer.h
        src/game/Components/IDComponent.cpp
        src/game/Components/IDComponent.h
        src/to_remove_or_modify/LoggerMenu.cpp
        src/to_remove_or_modify/LoggerMenu.h
        src/net/messaging/ObjectSerializer.cpp
        src/net/messaging/ObjectSerializer.h
        src/net/messaging/MessageParser.cpp
        src/net/messaging/MessageParser.h
        src/enumerates/MessageId.h

        # net
        src/net/Client.cpp
        src/net/Client.h
        src/net/Server.cpp
        src/net/Server.h
        src/net/UserConnection.cpp 
        src/net/UserConnection.h
        src/net/messaging/User.h src/enumerates/Color.h)

# create executable
add_executable(game ${SOURCE_FILES})

# link libraries
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${XMLPARSER})
