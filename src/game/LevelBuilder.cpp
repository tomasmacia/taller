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
#include "PhysicsComponent.h"
#include "StateComponent.h"
#include "IAComponent.h"
#include "../parser/config/npc.h"
#include "NPCRenderComponent.h"
#include "NonMovingRenderComponent.h"
#include "../parser/config/level.h"
#include "BackgroundRenderComponent.h"

#include <iostream>

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

    initializeCamera();
    initializeWorld();
    initializePlayers();
    initializeEnemies();
    //initializeWeapons();
    //initializeUtilities();
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("Inicializando Fondos");

    Manager *manager = Game::getInstance().getManager();
    Level currentLevelSprites = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);

    auto *overlay = manager->addEntity();
    overlay->addComponent<PositionComponent>(_camera);
    overlay->addComponent<BackgroundRenderComponent>(currentLevelSprites.overlay);

    auto *floor = manager->addEntity();
    floor->addComponent<PositionComponent>(_camera);
    floor->addComponent<BackgroundRenderComponent>(currentLevelSprites.floor);

    auto *middle = manager->addEntity();
    middle->addComponent<PositionComponent>(_camera);
    middle->addComponent<BackgroundRenderComponent>(currentLevelSprites.middle);

    auto *far = manager->addEntity();
    far->addComponent<PositionComponent>(_camera);
    far->addComponent<BackgroundRenderComponent>(currentLevelSprites.far);

    LogManager::logDebug("Fondos inicializados");
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("Inicializando Camara");

    Manager *manager = Game::getInstance().getManager();

    _camera = manager->addEntity();
    _camera->addComponent<CameraPositionComponent>();
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("Inicializando PJ");

    Manager *manager = Game::getInstance().getManager();

    for (auto &pj : Game::getInstance().getConfig()->gameplay.characters) {

        auto *player = manager->addEntity();
        _camera->getComponent<CameraPositionComponent>()->setPlayer(player);
        player->addComponent<InputComponent>();
        player->addComponent<PhysicsComponent>();
        player->addComponent<PositionComponent>(_camera);
        player->addComponent<CharacterRenderComponent>(&pj);
        player->addComponent<StateComponent>();
        //es imporante cuidar el orden de update (ESTE ES)


        LogManager::logDebug("Jugador inicializado");
    }
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("Inicializando enemigos");

    Manager *manager = Game::getInstance().getManager();

    auto npcs = Game::getInstance().getConfig()->gameplay.npcs;

    for (int i = 0; i < npcs.size();i++) {

        auto npcConfig = npcs.at(i);
        auto *npc = manager->addEntity();

        int x = generateX();
        int y = generateY();

        npc->addComponent<IAComponent>();
        npc->addComponent<PhysicsComponent>();
        npc->addComponent<PositionComponent>(_camera,x,y);
        npc->addComponent<NPCRenderComponent>(&npcConfig);
        npc->addComponent<StateComponent>();
    } 

    LogManager::logDebug("enemigos inicializados");
}

void LevelBuilder::initializeWeapons() {
    LogManager::logDebug("Inicializando armas");

    Manager *manager = Game::getInstance().getManager();

    auto weapons = Game::getInstance().getConfig()->gameplay.weapons;

    for (int i = 0; i < weapons.knife.amount;i++) {

        auto knifeConfig = weapons.knife;
        auto *knife = manager->addEntity();

        int x = generateX();
        int y = generateY();

        knife->addComponent<PositionComponent>(_camera,x,y);
        knife->addComponent<NonMovingRenderComponent>(knifeConfig.sprite);
    } 
    LogManager::logDebug("tubos de metal inicializados");

    for (int i = 0; i < weapons.tube.amount;i++) {

        auto tubeConfig = weapons.tube;
        auto *tube = manager->addEntity();

        int x = generateX();
        int y = generateY();

        tube->addComponent<PositionComponent>(_camera,x,y);
        tube->addComponent<NonMovingRenderComponent>(tubeConfig.sprite);
    }

    LogManager::logDebug("tubos de metal inicializados");
}

void LevelBuilder::initializeUtilities() {
    LogManager::logDebug("Inicializando cajas y barriles");

    Manager *manager = Game::getInstance().getManager();

    auto utilities = Game::getInstance().getConfig()->gameplay.utilities;

    for (int i = 0; i < utilities.box.amount;i++) {

        auto boxConfig = utilities.box;
        auto *box = manager->addEntity();

        int x = generateX();
        int y = generateY();

        box->addComponent<PositionComponent>(_camera,x,y);
        box->addComponent<NonMovingRenderComponent>(boxConfig.sprite);
    } 
    LogManager::logDebug("cajas inicializados");

    for (int i = 0; i < utilities.barrel.amount;i++) {

        auto barrelConfig = utilities.barrel;
        auto *barrel = manager->addEntity();

        int x = generateX();
        int y = generateY();

        barrel->addComponent<PositionComponent>(_camera,x,y);
        barrel->addComponent<NonMovingRenderComponent>(barrelConfig.sprite);
    }

    LogManager::logDebug("barriles inicializados");
}

int LevelBuilder::generateX(){
    return 0;
}

int LevelBuilder::generateY(){
    return 0; 
}


/*    vector<NPC> enemies = Game::getInstance().getConfig()->gameplay.npcs;
    Level level = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);

    for (auto &enemy : enemies) {
        int x;
        if (level.name == "bay") {
            x = rand() % (20001);
        } else if (level.name == "desert") {
            x = rand() % (20001/2);
        } else {
            x = rand() % (20001/2);
        }
        int y = 120 + rand() % (201 - 120);
        Game::getInstance().addGameComponent(new Game_Component(enemy.walk, x, y, Game::getInstance().getRenderer(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height,true,5)); // HARDCODE 5
        LogManager::logDebug("Enemigo inicializado");
    }*/




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