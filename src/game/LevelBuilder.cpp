//
// Created by Tomás Macía on 21/09/2019.
//

#include <vector>
#include "../parser/config/level.h"
#include "../parser/config/npc.h"
#include "LevelBuilder.h"
#include "GameServer.h"
#include "PositionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "StateComponent.h"
#include "IAComponent.h"
#include "NPCRenderComponent.h"
#include "CharacterRenderComponent.h"
#include "BackgroundRenderComponent.h"
#include "NonMobileRenderComponent.h"
#include "RenderComponent.h"
#include "CameraComponent.h"


#include <iostream>

using namespace std;

LevelBuilder::LevelBuilder() {
    currentLevel = 0;
    levelRunning = false;
    totalLevels = GameServer::getInstance().getConfig()->gameplay.levels.size();
    LogManager::logDebug(&"cantidad de niveles cargados: " [totalLevels]);
}

bool LevelBuilder::hasNextLevel(){
    LogManager::logInfo("se chequea si hay siguiente nivel");
    return currentLevel < totalLevels;
}

void LevelBuilder::loadNext() {

    if (currentLevel == 0){
        LogManager::logInfo("cargando primer nivel");
        initialize();
        levelRunning = true;
    }
    else{
        LogManager::logInfo("cargando siguiente nivel");
        prepareForNextLevel();
        initializeNextLevel();
        levelRunning = true;
    }
}

void LevelBuilder::endLevel(){
    levelRunning = false;
}

void LevelBuilder::prepareForNextLevel(){
    GameServer::getInstance().getManager()->prepareForNextLevel();
}

void LevelBuilder::initialize() {

    currentLevel = 1;
    LogManager::logInfo("=======================================");
    LogManager::logInfo(&"inicializando NIVEL " [currentLevel]);

    initializeCamera();
    initializeWorld();
    initializeLevelLimits();
    initializePlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeNextLevel() {

    currentLevel++;
    LogManager::logInfo("=======================================");
    LogManager::logInfo(&"inicializando NIVEL " [currentLevel]);

    resetCamera();
    initializeWorld();
    resetLevelLimits();
    resetPlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::resetCamera() {
    LogManager::logDebug("reseteando Camara");
    _camera->getComponent<CameraComponent>()->reset();
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("Inicializando Camara");

    Manager *manager = GameServer::getInstance().getManager();

    _camera = manager->addSpecialEntity();
    _camera->addComponent<CameraComponent>();
}

void LevelBuilder::resetLevelLimits() {
    LogManager::logDebug("reseteando limites de pantalla");

    int screenWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    int screenHeigth = GameServer::getInstance().getConfig()->screenResolution.height;

    _levelLimits->getComponent<LevelLimits>()->reset(screenWidth,screenHeigth,currentLevelWidth);
}

void LevelBuilder::initializeLevelLimits() {
    LogManager::logDebug("Inicializando limites de pantalla");

    Manager *manager = GameServer::getInstance().getManager();

    int screenWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    int screenHeigth = GameServer::getInstance().getConfig()->screenResolution.height;

    _levelLimits = manager->addSpecialEntity();
    _levelLimits->addComponent<LevelLimits>(screenWidth,screenHeigth,currentLevelWidth,_camera->getComponent<CameraComponent>());
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("Inicializando Fondos");

    Manager *manager = GameServer::getInstance().getManager();
    Level currentLevelSprites = GameServer::getInstance().getConfig()->gameplay.levels.at(currentLevel - 1);

    initializeLevelWidth(currentLevelSprites.floor.front());

    if (!currentLevelSprites.far.empty()){
        auto *far = manager->addBackLayerBackgrounds();
        far->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.far.front(), FAR_SPEED_RATIO);
    }

    if (!currentLevelSprites.middle.empty()){
        auto *middle = manager->addBackLayerBackgrounds();
        middle->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.middle.front(), MIDDLE_SPEED_RATIO);
    }

    if (!currentLevelSprites.floor.empty()){
        auto *floor = manager->addBackLayerBackgrounds();
        floor->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.floor.front(), FLOOR_SPEED_RATIO);
    }

    if (!currentLevelSprites.overlay.empty()){
        auto *overlay = manager->addFrontLayerBackgrounds();
        overlay->addComponent<BackgroundRenderComponent>(_camera, currentLevelSprites.overlay.front(), OVERLAY_SPEED_RATIO);
    }

    LogManager::logDebug("Fondos inicializados");
}

void LevelBuilder::initializeLevelWidth(std::string floorSpritePath){

    auto texture = new TextureWrapper();

    if(texture->loadFromFile(floorSpritePath)) {

        int screenResolutionWidth = GameServer::getInstance().getConfig()->screenResolution.width;
        int screenResolutionHeight = GameServer::getInstance().getConfig()->screenResolution.height;
        float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

        float scaleFactor =  (aspectRatio * (float)texture->getHeight())/screenResolutionWidth;

        currentLevelWidth = (float)texture->getWidth() / scaleFactor;
    }

    texture->free();
    delete(texture);
}

void LevelBuilder::resetPlayers() {
    LogManager::logDebug("reseteando jugadores");

    Manager *manager = GameServer::getInstance().getManager();

    int screenResolutionWidth = (int)(GameServer::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(GameServer::getInstance().getConfig()->screenResolution.height);
    int amountOfPlayers = manager->getPlayers().size();
    int offset = screenResolutionWidth/(amountOfPlayers+1);

    int i = 0;
    for (auto &pj : manager->getPlayers()) {
        
        int x = offset*(i+1);
        int y = screenResolutionHeight/2;

        pj->getComponent<PositionComponent>()->setPosition(x,y);

        i++;
    }
    LogManager::logDebug(&"Jugadores resetados: " [amountOfPlayers]);
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("Inicializando PJ");

    Manager *manager = GameServer::getInstance().getManager();

    int screenResolutionWidth = (int)(GameServer::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(GameServer::getInstance().getConfig()->screenResolution.height);
    int amountOfPlayers = GameServer::getInstance().getConfig()->gameplay.characters.size();
    int offset = screenResolutionWidth/(amountOfPlayers + 1);
    int i = 0;
    for (auto &pj : GameServer::getInstance().getConfig()->gameplay.characters) {
        
        int x = offset*(i+1);
        int y = screenResolutionHeight/2;

        auto *player = manager->addPlayer();
        _camera->getComponent<CameraComponent>()->setPlayer(player);
        player->addComponent<InputComponent>();
        player->addComponent<PhysicsComponent>(_levelLimits->getComponent<LevelLimits>());
        player->addComponent<PositionComponent>(x,y);
        player->addComponent<CharacterRenderComponent>(_camera, pj);
        player->addComponent<StateComponent>();
        //es imporante cuidar el orden de update (ESTE ES)

        LogManager::logDebug(&"Jugadores inicializados: " [amountOfPlayers]);
        i++;
    }
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("Inicializando enemigos");

    Manager *manager = GameServer::getInstance().getManager();

    int screenResolutionWidth = (int)(GameServer::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(GameServer::getInstance().getConfig()->screenResolution.height);

    auto npcs = GameServer::getInstance().getConfig()->gameplay.npcs;
    int amountOfEnemies = npcs.size();

    for (int i = 0; i < npcs.size();i++) {

        auto npcConfig = npcs.at(i);
        auto *npc = manager->addNPC();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        npc->addComponent<IAComponent>();
        npc->addComponent<PhysicsComponent>(_levelLimits->getComponent<LevelLimits>());
        npc->addComponent<PositionComponent>(x,y);
        npc->addComponent<NPCRenderComponent>(_camera, &npcConfig);
        npc->addComponent<StateComponent>();
    }

    LogManager::logDebug(&"Enemigos inicializados: " [amountOfEnemies]);
}

void LevelBuilder::initializeWeapons() {
    LogManager::logDebug("Inicializando armas");

    Manager *manager = GameServer::getInstance().getManager();

    auto weapons = GameServer::getInstance().getConfig()->gameplay.weapons;

    for (int i = 0; i < weapons.knife.amount;i++) {

        auto knifeConfig = weapons.knife;
        auto *knife = manager->addWeapon();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        knife->addComponent<PositionComponent>(x,y);
        knife->addComponent<NonMobileRenderComponent>(_camera, knifeConfig.sprite);
    }
    LogManager::logDebug(&"armas inicializadas: " [weapons.knife.amount]);

    for (int i = 0; i < weapons.tube.amount;i++) {

        auto tubeConfig = weapons.tube;
        auto *tube = manager->addWeapon();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        tube->addComponent<PositionComponent>(x,y);
        tube->addComponent<NonMobileRenderComponent>(_camera, tubeConfig.sprite);
    }    
    LogManager::logDebug(&"tubos de metal inicializados: " [weapons.tube.amount]);
}

void LevelBuilder::initializeUtilities() {
    LogManager::logDebug("Inicializando cajas y barriles");

    Manager *manager = GameServer::getInstance().getManager();

    auto utilities = GameServer::getInstance().getConfig()->gameplay.utilities;

    for (int i = 0; i < utilities.box.amount;i++) {

        auto boxConfig = utilities.box;
        auto *box = manager->addUtilitie();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        box->addComponent<PositionComponent>(x,y);
        box->addComponent<NonMobileRenderComponent>(_camera, boxConfig.sprite);
    } 
    LogManager::logDebug(&"cajas inicializadas: " [utilities.box.amount]);

    for (int i = 0; i < utilities.barrel.amount;i++) {

        auto barrelConfig = utilities.barrel;
        auto *barrel = manager->addUtilitie();

        int x = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenX();
        int y = _levelLimits->getComponent<LevelLimits>()->generateValidInScreenY();

        barrel->addComponent<PositionComponent>(x,y);
        barrel->addComponent<NonMobileRenderComponent>(_camera, barrelConfig.sprite);
    }
    LogManager::logDebug(&"barriles inicializados: " [utilities.barrel.amount]);
}

int LevelBuilder::getCurrentLevelWidth(){
    return currentLevelWidth;
}

LevelBuilder::~LevelBuilder(){
    _camera = nullptr;
    _levelLimits = nullptr;
    LogManager::logDebug("Memoria de LevelBuilder liberada");
}

bool LevelBuilder::levelFinished(){
    return levelRunning;
}
