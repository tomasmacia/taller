//
// Created by Tomás Macía on 21/09/2019.
//

#include <vector>
#include <algorithm>
#include "LevelBuilder.h"
#include "Game.h"
#include "PositionComponent.h"
#include "InputComponent.h"
#include "CameraPositionComponent.h"
#include "CharacterRenderComponent.h"

using namespace std;

LevelBuilder::LevelBuilder() {
    currentLevel = 1;
    totalLevels = Game::getInstance().getConfig()->gameplay.levels.size();
}

bool LevelBuilder::loadNext() {
    if (currentLevel > totalLevels) {
        return false;
    }

    initialize();
    currentLevel += 1;
    return true;
}

void LevelBuilder::initialize() {
    LogManager::logDebug(&"Incializando NIVEL " [currentLevel]);
    srand(time(nullptr));

    // destroy everything from previous level
    Game::getInstance().getManager()->destroyAllEntities();

    //initializeWorld();
    initializePlayers();
    //initializeEnemies();
    //initializeWeapons();
    //initializeUtilities();
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("Inicializando Fondos");

    Manager *manager = Game::getInstance().getManager();
    Level currentLevelSprites = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);

    if (!currentLevelSprites.floor.empty()) {
        //background = manager->addEntity();
    }

//    auto &background = manager->addEntity();
//
//    background.addComponent<>();
}

Entity& LevelBuilder::initializeCamera(Entity &player) {
    LogManager::logDebug("Inicializando Camara");

    Manager *manager = Game::getInstance().getManager();

    auto &camera = manager->addEntity();
    camera.addComponent<CameraPositionComponent>(player);

    return camera;
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("Inicializando PJ");

    Manager *manager = Game::getInstance().getManager();

    for (auto &pj : Game::getInstance().getConfig()->gameplay.characters) {

        auto &player = manager->addEntity();

        Entity& camera = initializeCamera(player);
        player.addComponent<PositionComponent>(&camera);
        //player.addComponent<InputComponent>(); // TODO check
        player.addComponent<CharacterRenderComponent>(&pj);



        LogManager::logDebug("Jugador inicializado");
    }
}
//
//void LevelBuilder::initializeEnemies() {
//    LogManager::logDebug("Inicializando enemigos");
//    vector<NPC> enemies = Game::getInstance().getConfig()->gameplay.npcs;
//    Level level = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);
//
//    for (auto &enemy : enemies) {
//        int x;
//        if (level.name == "bay") {
//            x = rand() % (20001);
//        } else if (level.name == "desert") {
//            x = rand() % (20001/2);
//        } else {
//            x = rand() % (20001/2);
//        }
//        int y = 120 + rand() % (201 - 120);
//        Game::getInstance().addGameComponent(new Game_Component(enemy.walk, x, y, Game::getInstance().getRenderer(),
//                Game::getInstance().getConfig()->screenResolution.width,
//                Game::getInstance().getConfig()->screenResolution.height,true,5)); // HARDCODE 5
//        LogManager::logDebug("Enemigo inicializado");
//    }
//}
//
//void LevelBuilder::initializeWeapons() {
//    LogManager::logDebug("Inicializando armas");
//    Weapons weapons = Game::getInstance().getConfig()->gameplay.weapons;
//    Level level = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);
//
//    for (int i = 0; i < weapons.tube.amount ; ++i) {
//        int x = 0;
//        if (level.name == "bay") {
//            x = rand() % (20001);
//        } else if (level.name == "desert") {
//            x = rand() % (20001/2);
//        } else {
//            x = rand() % (20001/2);
//        }
//        int y = 120 + rand() % (201 - 120);
//        Game::getInstance().addGameComponent(new Game_Component(weapons.tube.sprite, x, y,
//                Game::getInstance().getRenderer(),
//                Game::getInstance().getConfig()->screenResolution.width,
//                Game::getInstance().getConfig()->screenResolution.height,false,1)); // HARDCODED 1
//        LogManager::logDebug("Agregado tubo");
//    }
//
//    /* posiciones del cuchillos aleatoria en el rango del suelo */
//    for (int i = 0; i < weapons.knife.amount; ++i) {
//        int x = 0;
//        if (level.name == "bay") {
//            x = rand() % (20001);
//        } else if (level.name == "desert") {
//            x = rand() % (20001/2);
//        } else {
//            x = rand() % (20001/2);
//        }
//        int y = 120 + rand() % (201 - 120);
//        Game::getInstance().addGameComponent(new Game_Component(weapons.knife.sprite, x, y,
//                Game::getInstance().getRenderer(),
//                Game::getInstance().getConfig()->screenResolution.width,
//                Game::getInstance().getConfig()->screenResolution.height,false,1)); // HARDCODED 1
//        LogManager::logDebug("Agregado cuchillo");
//    }
//}
//
//void LevelBuilder::initializeUtilities() {
//    LogManager::logDebug("Inicializando utilidades");
//    Utilities utilities = Game::getInstance().getConfig()->gameplay.utilities;
//    Level level = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);
//
//    for (int i = 0; i < utilities.barrel.amount; ++i) {
//        int x = 0;
//        if (level.name == "bay") {
//            x = rand() % (20001);
//        } else if (level.name == "desert") {
//            x = rand() % (20001/2);
//        } else {
//            x = rand() % (20001/2);
//        }
//        int y = 120 + rand() % (201 - 120);
//        Game::getInstance().addGameComponent(new Game_Component(utilities.barrel.sprite, x, y,
//                Game::getInstance().getRenderer(),
//                Game::getInstance().getConfig()->screenResolution.width,
//                Game::getInstance().getConfig()->screenResolution.height,false,1)); // HARDCODED 1
//        LogManager::logDebug("Agregado barril");
//    }
//
//    for (int i = 0; i < utilities.box.amount; ++i) {
//        int x = 0;
//        if (level.name == "bay") {
//            x = rand() % (20001);
//        } else if (level.name == "desert") {
//            x = rand() % (20001/2);
//        } else {
//            x = rand() % (20001/2);
//        }
//        int y = 120 + rand() % (201 - 120);
//        Game::getInstance().addGameComponent(new Game_Component(utilities.box.sprite, x, y,
//                Game::getInstance().getRenderer(),
//                Game::getInstance().getConfig()->screenResolution.width,
//                Game::getInstance().getConfig()->screenResolution.height, false, 1)); // HARDCODED 1
//        LogManager::logDebug("Agregada caja");
//    }
//}
//
//std::vector<float> LevelBuilder::getParallaxSpeedPerLevel() {
//    std::vector<float> speeds;
//    Level level = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);
//
//    if (level.name == "bay") {
//        speeds = {0.063, 0.25, 0.5, 0.5};
//    } else if (level.name == "desert") {
//        speeds = {0.095, 0.25, 0.5, 0.5};
//    } else {
//        speeds = {0.13, 0.25, 0.5, 0.6};
//    }
//
//    return speeds;
//}