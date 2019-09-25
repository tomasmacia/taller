//
// Created by Tomás Macía on 21/09/2019.
//

#include <vector>
#include <algorithm>
#include "LevelBuilder.h"
#include "game.h"
#include "character.h"

using namespace std;

LevelBuilder::LevelBuilder() {
    currentLevel = 1;
    totalLevels = Game::getInstance().getConfig()->gameplay.levels.size();
    // initialize();
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
    Game::getInstance().destroyLevelObjects();

    initializeWorld();
    initializePlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();

    std::vector<Game_Component*> pepe = Game::getInstance().getGameComponents();

    sort(pepe.begin(), pepe.end(),[](Game_Component* i1, Game_Component* i2) {
        return (i1->GetPosY() < i2->GetPosY());
    });
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("Inicializando Fondos");
    Game::getInstance().setFloorSprites(Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1).floor);
//    Game::getInstance().setMiddleSprites(Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1).middle);
    Game::getInstance().setFarSprites(Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1).far);
    Game::getInstance().setOverlaySprites(Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1).overlay);

    Game::getInstance().setFarBackground(new Background(Game::getInstance().farSprites,
            Game::getInstance().getConfig()->screenResolution.height,
            Game::getInstance().getConfig()->screenResolution.width,
            Game::getInstance().getRenderer(), &Game::getInstance(), 0.063, 3)); //0.063

    Game::getInstance().setFloorBackground(new Background(Game::getInstance().floorSprites,
            Game::getInstance().getConfig()->screenResolution.height,
            Game::getInstance().getConfig()->screenResolution.width,
            Game::getInstance().getRenderer(), &Game::getInstance(), 0.5, 1)); //0.5

//    Game::getInstance().setMiddleBackground(new Background(Game::getInstance().middleSprites,
//            Game::getInstance().getConfig()->screenResolution.height,
//            Game::getInstance().getConfig()->screenResolution.width,
//            Game::getInstance().getRenderer(), &Game::getInstance(), 0.25, 3)); //0.25

    Game::getInstance().setOverlayBackground(new Background(Game::getInstance().overlaySprites,
            Game::getInstance().getConfig()->screenResolution.height,
            Game::getInstance().getConfig()->screenResolution.width,
            Game::getInstance().getRenderer(), &Game::getInstance(), 0.5, 4)); //0.5
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("Inicializando PJ");

    for (auto &pj : Game::getInstance().getConfig()->gameplay.characters) {
        std::vector<std::string> pathToPJSprites;

        // TODO esto es un asco, luego refactorizar a un mapa enum a string
        pathToPJSprites.push_back(pj.walk);
        pathToPJSprites.push_back(pj.jump);
        pathToPJSprites.push_back(pj.punch);
        pathToPJSprites.push_back(pj.crouch);
        pathToPJSprites.push_back(pj.stand);
        pathToPJSprites.push_back(pj.jumpkick);
        pathToPJSprites.push_back(pj.kick);

        Game::getInstance().setCharacter(new Character(&Game::getInstance(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height,
                Game::getInstance().getRenderer(),
                pathToPJSprites));

        LogManager::logDebug("Jugador inicializado");
    }
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("Inicializando enemigos");
    vector<NPC> enemies = Game::getInstance().getConfig()->gameplay.npcs;

    for (auto &enemy : enemies) {
        int x = -1000 + rand() % (20001 + 1000);
        int y = 120 + rand() % (201 - 120);
        Game::getInstance().addGameComponent(new Game_Component(enemy.walk, x, y, Game::getInstance().getRenderer(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height,true,5)); // HARDCODE 5
        LogManager::logDebug("Enemigo inicializado");
    }
}

void LevelBuilder::initializeWeapons() {
    LogManager::logDebug("Inicializando armas");
    Weapons weapons = Game::getInstance().getConfig()->gameplay.weapons;

    for (int i = 0; i < weapons.tube.amount ; ++i) {
        int x = rand() % (20001);
        int y = 120 + rand() % (201 - 120);
        Game::getInstance().addGameComponent(new Game_Component(weapons.tube.sprite, x, y,
                Game::getInstance().getRenderer(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height,false,1)); // HARDCODED 1
        LogManager::logDebug("Agregado tubo");
    }

    /* posiciones del cuchillos aleatoria en el rango del suelo */
    for (int i = 0; i < weapons.knife.amount; ++i) {
        int x = rand() % (20001);
        int y = 120 + rand() % (201 - 120);
        Game::getInstance().addGameComponent(new Game_Component(weapons.knife.sprite, x, y,
                Game::getInstance().getRenderer(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height,false,1)); // HARDCODED 1
        LogManager::logDebug("Agregado cuchillo");
    }
}

void LevelBuilder::initializeUtilities() {
    LogManager::logDebug("Inicializando utilidades");
    Utilities utilities = Game::getInstance().getConfig()->gameplay.utilities;

    for (int i = 0; i < utilities.barrel.amount; ++i) {
        int x = rand() % (20001 );
        int y = 120 + rand() % (201 - 120);
        Game::getInstance().addGameComponent(new Game_Component(utilities.barrel.sprite, x, y,
                Game::getInstance().getRenderer(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height,false,1)); // HARDCODED 1
        LogManager::logDebug("Agregado barril");
    }

    for (int i = 0; i < utilities.box.amount; ++i) {
        int x = rand() % (20001);
        int y = 120 + rand() % (201 - 120);
        Game::getInstance().addGameComponent(new Game_Component(utilities.box.sprite, x, y,
                Game::getInstance().getRenderer(),
                Game::getInstance().getConfig()->screenResolution.width,
                Game::getInstance().getConfig()->screenResolution.height, false, 1)); // HARDCODED 1
        LogManager::logDebug("Agregada caja");
    }
}