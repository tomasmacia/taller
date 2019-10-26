//
// Created by Tomás Macía on 21/09/2019.
//

#include <vector>
#include <algorithm>
#include "../parser/config/level.h"
#include "../parser/config/npc.h"
#include "LevelBuilder.h"
#include "Game.h"
#include "PositionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "StateComponent.h"
#include "IAComponent.h"
#include "NPCRenderComponent.h"
#include "CharacterRenderComponent.h"
#include "BackgroundRenderComponent.h"
#include "NonMobileRenderComponent.h"
#include "MobileRenderComponent.h"
#include "RenderComponent.h"
#include "CameraComponent.h"


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

    // destroy everything from previous level
    Game::getInstance().getManager()->destroyAllEntities();

    initializeCamera();
    initializeWorld();
    initializeLevelLimits();
    initializePlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("Inicializando Camara");

    Manager *manager = Game::getInstance().getManager();

    _camera = manager->addEntity();
    _camera->addComponent<CameraComponent>();
}

void LevelBuilder::initializeLevelLimits() {
    LogManager::logDebug("Inicializando limites de pantalla");

    Manager *manager = Game::getInstance().getManager();

    int screenWidth = Game::getInstance().getConfig()->screenResolution.width;
    int screenHeigth = Game::getInstance().getConfig()->screenResolution.height;

    _levelLimits = manager->addEntity();
    _levelLimits->addComponent<LevelLimits>(screenWidth,screenHeigth,currentLevelWidth,_camera->getComponent<CameraComponent>());
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("Inicializando Fondos");

    Manager *manager = Game::getInstance().getManager();
    Level currentLevelSprites = Game::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);

    initializeApropiateParallaxSpeeds(currentLevelSprites);

    auto *far = manager->addEntity();
    far->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.far.front(),_farSpeedRatio);

    auto *middle = manager->addEntity();
    middle->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.middle.front(),_middleSpeedRatio);

    auto *floor = manager->addEntity();
    floor->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.floor.front(),_floorSpeedRatio);
    
    auto *overlay = manager->addEntity();
    overlay->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.overlay.front(),_overlaySpeedRatio);

    LogManager::logDebug("Fondos inicializados");
}

void LevelBuilder::initializeApropiateParallaxSpeeds(Level currentLevelSprites){

    _texture = new TextureWrapper(); 

    float screenResolutionWidth = (int)(Game::getInstance().getConfig()->screenResolution.width);
    float screenResolutionHeight = (int)(Game::getInstance().getConfig()->screenResolution.height);

    float aspectRatio = screenResolutionWidth/screenResolutionHeight;

    _texture->loadFromFile(currentLevelSprites.far.front());
    float farWidth = _texture->getWidth();
    float farHeigth = _texture->getHeight();

    _texture->loadFromFile(currentLevelSprites.middle.front());
    float middleWidth = _texture->getWidth();
    float middleHeigth = _texture->getHeight();

    _texture->loadFromFile(currentLevelSprites.floor.front());
    float floorWidth = _texture->getWidth();
    float floorHeigth = _texture->getHeight();

    _texture->loadFromFile(currentLevelSprites.overlay.front());
    float overlayWidth = _texture->getWidth();
    float overlayHeigth = _texture->getHeight();


    _floorSpeedRatio = 0.2;
    currentLevelWidth = floorWidth/_floorSpeedRatio;
    _farSpeedRatio = (farWidth - aspectRatio*farHeigth)/(floorWidth - screenResolutionWidth)*_floorSpeedRatio;
    _middleSpeedRatio = (middleWidth - aspectRatio*middleHeigth)/(floorWidth - screenResolutionWidth)*_floorSpeedRatio;
    _overlaySpeedRatio = _floorSpeedRatio;
    //aca en el overlay la logica es distinta porque nosotros tapamos el background de floor con otro en vez de editarlo

    _texture->free();
    delete(_texture);
    _texture = nullptr;
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("Inicializando PJ");

    Manager *manager = Game::getInstance().getManager();

    int screenResolutionWidth = (int)(Game::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(Game::getInstance().getConfig()->screenResolution.height);
    int amountOfPlayers = Game::getInstance().getConfig()->gameplay.characters.size();
    int offset = screenResolutionWidth/(amountOfPlayers+1);

    int i = 0;
    for (auto &pj : Game::getInstance().getConfig()->gameplay.characters) {
        
        int x = offset*(i+1);
        int y = screenResolutionHeight/2;

        auto *player = manager->addEntity();
        _camera->getComponent<CameraComponent>()->setPlayer(player);
        player->addComponent<InputComponent>();
        player->addComponent<PhysicsComponent>(_levelLimits->getComponent<LevelLimits>());
        player->addComponent<PositionComponent>(x,y);
        player->addComponent<CharacterRenderComponent>(_camera, pj);
        player->addComponent<StateComponent>();
        //es imporante cuidar el orden de update (ESTE ES)

        LogManager::logDebug("Jugador inicializado");
        i++;
    }
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("Inicializando enemigos");

    Manager *manager = Game::getInstance().getManager();

    int screenResolutionWidth = (int)(Game::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(Game::getInstance().getConfig()->screenResolution.height);

    auto npcs = Game::getInstance().getConfig()->gameplay.npcs;
    int amountOfEnemies = npcs.size();
    int offset = screenResolutionWidth/(amountOfEnemies+1);

    for (int i = 0; i < npcs.size();i++) {

        auto npcConfig = npcs.at(i);
        auto *npc = manager->addEntity();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        npc->addComponent<IAComponent>();
        npc->addComponent<PhysicsComponent>(_levelLimits->getComponent<LevelLimits>());
        npc->addComponent<PositionComponent>(x,y);
        npc->addComponent<NPCRenderComponent>(_camera, &npcConfig);
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

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        knife->addComponent<PositionComponent>(x,y);
        knife->addComponent<NonMobileRenderComponent>(_camera, knifeConfig.sprite);
    } 
    LogManager::logDebug("cuchillos inicializados");

    for (int i = 0; i < weapons.tube.amount;i++) {

        auto tubeConfig = weapons.tube;
        auto *tube = manager->addEntity();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        tube->addComponent<PositionComponent>(x,y);
        tube->addComponent<NonMobileRenderComponent>(_camera, tubeConfig.sprite);
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

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        box->addComponent<PositionComponent>(x,y);
        box->addComponent<NonMobileRenderComponent>(_camera, boxConfig.sprite);
    } 
    LogManager::logDebug("cajas inicializadas");

    for (int i = 0; i < utilities.barrel.amount;i++) {

        auto barrelConfig = utilities.barrel;
        auto *barrel = manager->addEntity();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        barrel->addComponent<PositionComponent>(x,y);
        barrel->addComponent<NonMobileRenderComponent>(_camera, barrelConfig.sprite);
    }
    LogManager::logDebug("barriles inicializados");
}

int LevelBuilder::getCurrentLevelWidth(){
    return currentLevelWidth;
}

LevelBuilder::~LevelBuilder(){
    delete(_texture);
    _texture = nullptr;
}