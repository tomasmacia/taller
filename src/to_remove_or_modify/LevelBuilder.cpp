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
LevelBuilder::LevelBuilder() {
    currentLevel = 0;
    levelRunning = false;
    totalLevels = GameServer::getInstance().getConfig()->gameplay.levels.size();
    LogManager::logDebug("[LEVEL]: Cantidad de niveles cargados: " + std::to_string(totalLevels));
}

//API
//=========================================================================================
void LevelBuilder::loadNext() {

    if (currentLevel == 0){
        LogManager::logInfo("[LEVEL]: cargando primer nivel");
        initialize();
        levelRunning = true;
    }
    else{
        LogManager::logInfo("[LEVEL]: cargando siguiente nivel");
        prepareForNextLevel();
        initializeNextLevel();
        levelRunning = true;
    }
}

bool LevelBuilder::hasNextLevel(){
    LogManager::logInfo("[LEVEL]: se chequea si hay siguiente nivel");
    return currentLevel < totalLevels;
}

bool LevelBuilder::levelFinished(){
    return _screen->isAtEnd();
}

//MANAGING OWN STATE
//=========================================================================================
void LevelBuilder::prepareForNextLevel(){
    GameServer::getInstance().getManager()->prepareForNextLevel();
}

//INITIALIZING LEVEL
//=========================================================================================
void LevelBuilder::initialize() {

    currentLevel = 1;
    LogManager::logInfo("=======================================");
    LogManager::logInfo("[LEVEL]: Inicializando NIVEL " + std::to_string(currentLevel));

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
    LogManager::logInfo("[LEVEL]: Inicializando NIVEL " + std::to_string(currentLevel));

    resetCamera();
    initializeWorld();
    resetLevelLimits();
    resetPlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("[LEVEL]: Inicializando Camara");

    Manager *manager = GameServer::getInstance().getManager();

    _camera = manager->addSpecialEntity();
    _camera->addComponent<Screen>();
}

void LevelBuilder::initializeLevelLimits() {
    LogManager::logDebug("[LEVEL]: Inicializando limites de pantalla");

    Manager *manager = GameServer::getInstance().getManager();

    int screenWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    int screenHeigth = GameServer::getInstance().getConfig()->screenResolution.height;

    _characterLevelLimits = manager->addSpecialEntity();
    _characterLevelLimits->addComponent<CharacterLevelLimits>(screenWidth,screenHeigth,currentLevelWidth,_camera->getComponent<Screen>());

    _nonCharacterLevelLimits = manager->addSpecialEntity();
    _nonCharacterLevelLimits->addComponent<NonCharacterLevelLimits>(screenWidth,screenHeigth,currentLevelWidth,_camera->getComponent<Screen>());

}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("[LEVEL]: Inicializando Fondos");

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

    LogManager::logDebug("[LEVEL]: Fondos inicializados");
}

void LevelBuilder::initializeLevelWidth(std::string floorSpritePath){

    ImageSize imageSize = ImageUtils::getImageSize(floorSpritePath);
    int floorSpriteWidth = imageSize.width;
    int floorSpriteHeight = imageSize.height;
    //TextureWrapper::measureWidthAndHeighthOf(floorSpritePath, &floorSpriteWidth, &floorSpriteHeight);

    int screenResolutionWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    int screenResolutionHeight = GameServer::getInstance().getConfig()->screenResolution.height;
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    float scaleFactor =  (aspectRatio * (float)floorSpriteHeight)/screenResolutionWidth;

    currentLevelWidth = (float)floorSpriteWidth/ scaleFactor;
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("[LEVEL]: Inicializando PJ");

    Manager *manager = GameServer::getInstance().getManager();

    int screenResolutionWidth = (int)(GameServer::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(GameServer::getInstance().getConfig()->screenResolution.height);
    int amountOfPlayers = GameServer::getInstance().getConfig()->gameplay.characters.size();
    int offset = (screenResolutionWidth - _camera->getComponent<Screen>()->getMargin()) / (amountOfPlayers + 1);
    int i = 0;
    auto charactersConfigs = GameServer::getInstance().getConfig()->gameplay.characters;


    IDManager::getInstance().initIDCounter();
    for (int i = 0; i < GameServer::getInstance().getMaxPlayers(); i++) {

        auto characterConfig = charactersConfigs[i];
        
        int x = offset*(i+1);
        int y = screenResolutionHeight/2;

        auto *player = manager->addPlayer();
        _camera->getComponent<Screen>()->setPlayer(player);
        player->addComponent<IDComponent>(IDManager::getInstance().getNextId());
        player->addComponent<InputComponent>();
        player->addComponent<PhysicsComponent>(_characterLevelLimits->getComponent<CharacterLevelLimits>());
        player->addComponent<PositionComponent>(x,y);
        player->addComponent<CharacterRenderComponent>(_camera, characterConfig);
        player->addComponent<StateComponent>();
        //es imporante cuidar el orden de update (ESTE ES)

    }
    LogManager::logDebug("[LEVEL]: Jugadores inicializados: " + std::to_string(amountOfPlayers));
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("[LEVEL]: Inicializando enemigos");

    Manager *manager = GameServer::getInstance().getManager();

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

    Manager *manager = GameServer::getInstance().getManager();

    auto weapons = GameServer::getInstance().getConfig()->gameplay.weapons;

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

    Manager *manager = GameServer::getInstance().getManager();

    auto utilities = GameServer::getInstance().getConfig()->gameplay.utilities;

    for (int i = 0; i < utilities.box.amount;i++) {

        auto boxConfig = utilities.box;
        auto *box = manager->addUtilitie();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        box->addComponent<PositionComponent>(x,y);
        box->addComponent<NonMobileRenderComponent>(_camera, boxConfig.sprite);
    } 
    LogManager::logDebug("[LEVEL]: Cajas inicializadas: " + std::to_string(utilities.box.amount));

    for (int i = 0; i < utilities.barrel.amount;i++) {

        auto barrelConfig = utilities.barrel;
        auto *barrel = manager->addUtilitie();

        int x = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenX();
        int y = _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->generateValidInScreenY();

        barrel->addComponent<PositionComponent>(x,y);
        barrel->addComponent<NonMobileRenderComponent>(_camera, barrelConfig.sprite);
    }
    LogManager::logDebug("[LEVEL]: Barriles inicializados: " + std::to_string(utilities.barrel.amount));
}

void LevelBuilder::resetLevelLimits() {
    LogManager::logDebug("[LEVEL]: reseteando limites de pantalla");

    int screenWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    int screenHeigth = GameServer::getInstance().getConfig()->screenResolution.height;

    _characterLevelLimits->getComponent<CharacterLevelLimits>()->reset(screenWidth,screenHeigth,currentLevelWidth);
    _nonCharacterLevelLimits->getComponent<NonCharacterLevelLimits>()->reset(screenWidth,screenHeigth,currentLevelWidth);
}

void LevelBuilder::resetPlayers() {
    LogManager::logDebug("[LEVEL]: reseteando jugadores");

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
    LogManager::logDebug("[LEVEL]: Jugadores resetados: " + std::to_string(amountOfPlayers));
}

void LevelBuilder::resetCamera() {
    LogManager::logDebug("[LEVEL]: reseteando Camara");
    _camera->getComponent<Screen>()->reset();
}


//DESTROY
//=========================================================================================
LevelBuilder::~LevelBuilder(){
    _camera = nullptr;
    _characterLevelLimits = nullptr;
    _nonCharacterLevelLimits = nullptr;
    LogManager::logDebug("[LEVEL]: Memoria de LevelBuilder liberada");
}
