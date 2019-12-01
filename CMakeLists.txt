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
        src/XMLparser/config/weaponConfig.h
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
        src/game/EntityManager.h
        src/game/EntityManager.cpp
        src/enumerates/Action.h
        src/to_remove_or_modify/LevelBuilder.h
        src/to_remove_or_modify/LevelBuilder.cpp
        src/entities/components/Position.h
        src/entities/components/Position.cpp
        src/entities/Screen.cpp
        src/entities/Screen.h
        src/image/TextureWrapper.cpp
        src/image/TextureWrapper.h
        src/entities/components/Physics.cpp
        src/entities/components/Physics.h
        src/entities/components/State.cpp
        src/entities/components/State.h
        src/entities/components/InputPoller.cpp
        src/entities/components/InputPoller.h
        src/entities/components/IA.h
        src/entities/components/IA.cpp
        src/entities/components/appearances/Appearance.h
        src/entities/components/appearances/Appearance.cpp
        src/entities/components/appearances/CharacterAppearance.h
        src/entities/components/appearances/CharacterAppearance.cpp
        src/entities/components/appearances/EnemyAppearance.h
        src/entities/components/appearances/EnemyAppearance.cpp
        src/entities/components/appearances/BackgroundAppearance.h
        src/entities/components/appearances/BackgroundAppearance.cpp
        src/entities/components/appearances/StateDrivenAppearance.cpp
        src/entities/components/appearances/StateDrivenAppearance.h
        src/to_remove_or_modify/LevelLimits.h
        src/to_remove_or_modify/LevelLimits.cpp
        src/to_remove_or_modify/CharacterLevelLimits.cpp
        src/to_remove_or_modify/CharacterLevelLimits.h
        src/to_remove_or_modify/NonCharacterLevelLimits.cpp
        src/to_remove_or_modify/NonCharacterLevelLimits.h

        src/net/messaging/Renderable.h
        src/net/messaging/Renderable.cpp
        src/net/messaging/IDManager.cpp
        src/net/messaging/IDManager.h
        src/entities/components/ID.cpp
        src/entities/components/ID.h
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
        src/net/messaging/User.h src/enumerates/Color.h src/entities/Character.cpp src/entities/Character.h src/net/messaging/Sendable.cpp src/net/messaging/Sendable.h src/net/messaging/Soundable.cpp src/net/messaging/Soundable.h src/entities/Life.cpp src/entities/Life.h src/entities/Score.cpp src/entities/Score.h src/entities/components/Damage.cpp src/entities/components/Damage.h src/entities/components/Will.cpp src/entities/components/Will.h src/entities/Enemy.cpp src/entities/Enemy.h src/entities/Barrel.cpp src/entities/Barrel.h src/entities/Tube.cpp src/entities/Tube.h src/entities/Box.cpp src/entities/Box.h src/entities/Knife.cpp src/entities/Knife.h src/entities/FinalBoss.cpp src/entities/FinalBoss.h src/entities/components/Sound.cpp src/entities/components/Sound.h src/image/Rect.cpp src/image/Rect.h src/entities/components/collition/CollitionHandler.cpp src/entities/components/collition/CollitionHandler.h src/entities/components/collition/CollitionBox.cpp src/entities/components/collition/CollitionBox.h src/game/CollitionManager.cpp src/game/CollitionManager.h src/entities/components/collition/AnimatedEntityCollitionHandler.cpp src/entities/components/collition/AnimatedEntityCollitionHandler.h src/entities/entityHierarchy/Entity.cpp src/entities/entityHierarchy/Entity.h src/entities/entityHierarchy/PhysicalEntity.cpp src/entities/entityHierarchy/PhysicalEntity.h src/entities/Background.cpp src/entities/Background.h src/entities/components/collition/BackgroundCollitionHandler.cpp src/entities/components/collition/BackgroundCollitionHandler.h src/entities/entityHierarchy/Utillity.cpp src/entities/entityHierarchy/Utillity.h src/entities/entityHierarchy/Weapon.cpp src/entities/entityHierarchy/Weapon.h src/entities/entityHierarchy/UnanimatedEntity.cpp src/entities/entityHierarchy/UnanimatedEntity.h src/entities/components/collition/ScreenCollitionHandler.cpp src/entities/components/collition/ScreenCollitionHandler.h src/entities/components/ScreenPosition.cpp src/entities/components/ScreenPosition.h src/entities/entityHierarchy/AnimatedEntity.cpp src/entities/entityHierarchy/AnimatedEntity.h src/entities/components/appearances/ScoreAppearance.cpp src/entities/components/appearances/ScoreAppearance.h src/entities/components/appearances/LifeAppearance.cpp src/entities/components/appearances/LifeAppearance.h src/enumerates/AttackCode.h src/entities/components/Attack.cpp src/entities/components/Attack.h src/entities/components/appearances/FinalBossAppearance.cpp src/entities/components/appearances/FinalBossAppearance.h)

# create executable
add_executable(game ${SOURCE_FILES})

# link libraries
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${XMLPARSER})
