//
// Created by Tomás Macía on 21/09/2019.
//

#include <vector>
#include <iostream>
#include "LevelBuilder.h"
#include "game.h"

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
    initializeWorld();
    initializePlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeWorld() {}

void LevelBuilder::initializePlayers() {
    cout << "Agregado Cody" << endl;
    //Game::getInstance().addGameObject(new GameObject("resources/cody.png", 0, 0));
}

void LevelBuilder::initializeEnemies() {
    vector<NPC> enemies = Game::getInstance().getConfig()->gameplay.npcs;

    for (auto enemy : enemies) {
        cout << "Agregando enemigo" << endl;
    }
}

void LevelBuilder::initializeWeapons() {
    Weapons weapons = Game::getInstance().getConfig()->gameplay.weapons;

    for (int i = 0; i < weapons.tube.amount ; ++i) {
        cout << "Agregando tubo" << endl;
    }

    for (int i = 0; i < weapons.knife.amount; ++i) {
        cout << "Agregando cuchillo" << endl;
    }
}

void LevelBuilder::initializeUtilities() {
    Utilities utilities = Game::getInstance().getConfig()->gameplay.utilities;

    for (int i = 0; i < utilities.barrel.amount; ++i) {
        cout << "Agregando barril" << endl;
    }

    for (int i = 0; i < utilities.box.amount; ++i) {
        cout << "Agregando caja" << endl;
    }
}