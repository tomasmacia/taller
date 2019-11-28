//
// Created by Tomás Macía on 21/09/2019.
//

#include "../XMLparser/config/level.h"
#include "../XMLparser/config/npc.h"
#include "../image/ImageUtils.h"

#include "LevelBuilder.h"

#include "../game/GameServer.h"
#include "../net/messaging/IDManager.h"

#include "CharacterLevelLimits.h"
#include "NonCharacterLevelLimits.h"

#include "../game/Components/PositionComponent.h"
#include "../game/Components/InputComponent.h"
#include "../game/Components/PhysicsComponent.h"
#include "../game/Components/StateComponent.h"
#include "../game/Components/IAComponent.h"
#include "../entities/Screen.h"
#include "../game/Components/IDComponent.h"

#include "../game/Components/Appearences/NPCRenderComponent.h"
#include "../game/Components/Appearences/CharacterRenderComponent.h"
#include "../game/Components/Appearences/BackgroundRenderComponent.h"
#include "../game/Components/Appearences/NonMobileRenderComponent.h"
#include "../game/Components/Appearences/RenderComponent.h"




using namespace std;

//CONSTRUCTOR
//=========================================================================================
LevelBuilder::LevelBuilder(Manager* manager, Config* config) {
    currentLevel = 0;
    _config = config;
    _levelAmount = _config->gameplay.levels.size();
    _manager = manager;

    LogManager::logDebug("[LEVEL]: Cantidad de niveles cargados: " + std::to_string(_levelAmount));
}

//API
//=========================================================================================
void LevelBuilder::loadNext() {

    if (currentLevel == 0){
        LogManager::logInfo("[LEVEL]: cargando primer nivel");
        initialize();
    }
    else{
        LogManager::logInfo("[LEVEL]: cargando siguiente nivel");
        prepareForNextLevel();
        initializeNextLevel();
    }
}

bool LevelBuilder::hasNextLevel(){
    LogManager::logInfo("[LEVEL]: se chequea si hay siguiente nivel");
    return currentLevel < _levelAmount;
}

bool LevelBuilder::levelFinished(){
    return _screen->isAtEnd();
}

//MANAGING OWN STATE
//=========================================================================================
void LevelBuilder::prepareForNextLevel(){
    _manager->prepareForNextLevel();
}

//INITIALIZING LEVEL
//=========================================================================================
void LevelBuilder::initialize() {

    currentLevel = 1;
    LogManager::logInfo("=======================================");
    LogManager::logInfo("[LEVEL]: Inicializando NIVEL " + std::to_string(currentLevel));

    initializeCollitionManager();
    initializeCamera();
    initializeWorld();
    initializePlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeNextLevel() {

    currentLevel++;
    LogManager::logInfo("=======================================");
    LogManager::logInfo("[LEVEL]: Inicializando NIVEL " + std::to_string(currentLevel));

    resetCamera();
    initializeWorld();
    resetPlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeCollitionManager(){
    LogManager::logDebug("[LEVEL]: Inicializando Collition Manager");
    _collitionManager = new CollitionManager();
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("[LEVEL]: Inicializando Camara");

    _screen = new Screen(_config->screenResolution.width, _config->screenResolution.height);
    _manager->addScreen(_screen);
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("[LEVEL]: Inicializando Fondos");

    Level currentLevelSprites = _config->gameplay.levels.at(currentLevel - 1);

    initializeLevelWidth(currentLevelSprites.floor.front());

    if (!currentLevelSprites.far.empty()){

        string stritePath = currentLevelSprites.far.front();
        auto *far = new Background(_screen, stritePath, FAR_SPEED_RATIO, _collitionManager, nullptr);
        _manager->addBackLayerBackgrounds(far);
    }

    if (!currentLevelSprites.middle.empty()){

        string stritePath = currentLevelSprites.middle.front()
        auto *middle = new Background(_screen, stritePath, MIDDLE_SPEED_RATIO, _collitionManager, nullptr);
        _manager->addBackLayerBackgrounds(middle);
    }

    if (!currentLevelSprites.floor.empty()){

        string stritePath = currentLevelSprites.floor.front()
        auto *floor = new Background(_screen, stritePath, FLOOR_SPEED_RATIO, _collitionManager, nullptr);
        _manager->addBackLayerBackgrounds(floor);
    }

    if (!currentLevelSprites.overlay.empty()){

        string stritePath = currentLevelSprites.overlay.front()
        auto *overlay = new Background(_screen, stritePath, OVERLAY_SPEED_RATIO, _collitionManager, nullptr);
        _manager->addBackLayerBackgrounds(overlay);
    }
    LogManager::logDebug("[LEVEL]: Fondos inicializados");
}

void LevelBuilder::initializeLevelWidth(std::string floorSpritePath){

    ImageSize imageSize = ImageUtils::getImageSize(floorSpritePath);
    int floorSpriteWidth = imageSize.width;
    int floorSpriteHeight = imageSize.height;

    int screenResolutionWidth = _config->screenResolution.width;
    int screenResolutionHeight = _config->screenResolution.height;
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    float scaleFactor =  (aspectRatio * (float)floorSpriteHeight)/screenResolutionWidth;

    currentLevelWidth = (float)floorSpriteWidth/ scaleFactor;

    _screen->setLevelWidth(currentLevelWidth);
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("[LEVEL]: Inicializando PJ");

    int screenResolutionWidth = (int)(_config->screenResolution.width);
    int screenResolutionHeight = (int)(_config->screenResolution.height);
    int amountOfPlayers = _config->gameplay.characters.size();

    int offset = (screenResolutionWidth - _screen->getMargin()) / (amountOfPlayers + 1);
    int i = 0;
    auto charactersConfigs = _config->gameplay.characters;

    IDManager::getInstance().initIDCounter();
    for (int i = 0; i < amountOfPlayers; i++) {

        auto characterConfig = charactersConfigs[i];
        int newPlayerID = IDManager::getInstance().getNextId();
        
        int x = offset*(i+1);
        int y = screenResolutionHeight/2;
        int z = 0;




        IDManager::getInstance().getNextId();
        auto *player = _manager->addPlayer(newPlayerID);


        _screen->setPlayer(player);

    }
    LogManager::logDebug("[LEVEL]: Jugadores inicializados: " + std::to_string(amountOfPlayers));
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("[LEVEL]: Inicializando enemigos");

    int screenResolutionWidth = (int)(GameServer::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(GameServer::getInstance().getConfig()->screenResolution.height);

    auto npcs = GameServer::getInstance().getConfig()->gameplay.npcs;
    int amountOfEnemies = npcs.size();

    for (int i = 0; i < npcs.size();i++) {

        auto npcConfig = npcs.at(i);
        auto *npc = manager->addNPC();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        npc->addComponent<IAComponent>();
        npc->addComponent<PhysicsComponent>(_nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>());
        npc->addComponent<PositionComponent>(x,y);
        npc->addComponent<NPCRenderComponent>(_camera, &npcConfig);
        npc->addComponent<StateComponent>();
    }
    LogManager::logDebug("[LEVEL]: Enemigos inicializados: " + std::to_string(amountOfEnemies));
}

void LevelBuilder::initializeWeapons() {
    LogManager::logDebug("[LEVEL]: Inicializando armas");

    auto weapons = _config->gameplay.weapons;

    for (int i = 0; i < weapons.knife.amount;i++) {

        auto knifeConfig = weapons.knife;
        auto *knife = manager->addWeapon();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        knife->addComponent<PositionComponent>(x,y);
        knife->addComponent<NonMobileRenderComponent>(_camera, knifeConfig.sprite);
    }
    LogManager::logDebug("[LEVEL]: Armas inicializadas: " + std::to_string(weapons.knife.amount));

    for (int i = 0; i < weapons.tube.amount;i++) {

        auto tubeConfig = weapons.tube;
        auto *tube = manager->addWeapon();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        tube->addComponent<PositionComponent>(x,y);
        tube->addComponent<NonMobileRenderComponent>(_camera, tubeConfig.sprite);
    }    
    LogManager::logDebug("[LEVEL]: Tubos de metal inicializados: " + std::to_string(weapons.tube.amount));
}

void LevelBuilder::initializeUtilities() {
    LogManager::logDebug("[LEVEL]: Inicializando cajas y barriles");

    auto utilities = _config->gameplay.utilities;

    for (int i = 0; i < utilities.box.amount;i++) {

        auto boxConfig = utilities.box;
        auto *box = manager->addUtilitiy();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        box->addComponent<PositionComponent>(x,y);
        box->addComponent<NonMobileRenderComponent>(_camera, boxConfig.sprite);
    } 
    LogManager::logDebug("[LEVEL]: Cajas inicializadas: " + std::to_string(utilities.box.amount));

    for (int i = 0; i < utilities.barrel.amount;i++) {

        auto barrelConfig = utilities.barrel;
        auto *barrel = manager->addUtilitiy();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        barrel->addComponent<PositionComponent>(x,y);
        barrel->addComponent<NonMobileRenderComponent>(_camera, barrelConfig.sprite);
    }
    LogManager::logDebug("[LEVEL]: Barriles inicializados: " + std::to_string(utilities.barrel.amount));
}

void LevelBuilder::resetPlayers() {
    LogManager::logDebug("[LEVEL]: reseteando jugadores");

    int screenResolutionWidth = (int)(_config->screenResolution.width);
    int screenResolutionHeight = (int)(_config->screenResolution.height);
    int amountOfPlayers = _manager->getPlayers().size();
    int offset = screenResolutionWidth/(amountOfPlayers+1);

    int i = 0;
    for (auto &pj : _manager->getPlayers()) {

        int x = offset*(i+1);
        int y = screenResolutionHeight/2;

        pj->getComponent<PositionComponent>()->setPosition(x,y);

        i++;
    }
    LogManager::logDebug("[LEVEL]: Jugadores resetados: " + std::to_string(amountOfPlayers));
}

void LevelBuilder::resetCamera() {
    LogManager::logDebug("[LEVEL]: reseteando Camara");
    _screen->reset();
}

LevelBuilder::~LevelBuilder(){
    delete(_collitionManager);
}
