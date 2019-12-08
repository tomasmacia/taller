//
// Created by Tomás Macía on 21/09/2019.
//


#include "../image/ImageUtils.h"
#include "LevelBuilder.h"
#include "../net/messaging/IDManager.h"
#include "../entities/Character.h"




using namespace std;

//CONSTRUCTOR
//=========================================================================================
LevelBuilder::LevelBuilder(Controller* controller, Config* config) {
    currentLevel = 0;
    _config = config;
    _levelAmount = _config->gameplay.levels.size();
    _entityManager = new EntityManager(controller, config);

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
    _entityManager->prepareForNextLevel();
}

//INITIALIZING LEVEL
//=========================================================================================
void LevelBuilder::initialize() {

    currentLevel = 1;
    LogManager::logInfo("=======================================");
    LogManager::logInfo("[LEVEL]: Inicializando NIVEL " + std::to_string(currentLevel));

    initializeLevelDimentions();
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

    initializeLevelDimentions();
    resetCamera();
    initializeWorld();
    resetPlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("[LEVEL]: Inicializando Camara");
    _screen = _entityManager->addScreen(_config->screenResolution.width, _config->screenResolution.height, currentLevelWidth, currentlevelDepth);
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("[LEVEL]: Inicializando Fondos");

    Level currentLevelSprites = _config->gameplay.levels.at(currentLevel - 1);

    if (!currentLevelSprites.far.empty()){

        string stritePath = currentLevelSprites.far.front();
        _entityManager->addFar(stritePath,FAR_SPEED_RATIO);
    }

    if (!currentLevelSprites.middle.empty()){

        string stritePath = currentLevelSprites.middle.front();
        _entityManager->addMiddle(stritePath, MIDDLE_SPEED_RATIO);
    }

    if (!currentLevelSprites.floor.empty()){

        string stritePath = currentLevelSprites.floor.front();
        _entityManager->addFloor(stritePath, FLOOR_SPEED_RATIO);
    }

    if (!currentLevelSprites.overlay.empty()){

        string stritePath = currentLevelSprites.overlay.front();
        _entityManager->addOverlay(stritePath, OVERLAY_SPEED_RATIO);
    }
    LogManager::logDebug("[LEVEL]: Fondos inicializados");
}

void LevelBuilder::initializeLevelDimentions(){

    std::string floorSpritePath = _config->gameplay.levels.at(currentLevel - 1).floor.front();

    ImageSize imageSize = ImageUtils::getImageSize(floorSpritePath);
    int floorSpriteWidth = imageSize.width;
    int floorSpriteHeight = imageSize.height;

    int screenResolutionWidth = _config->screenResolution.width;
    int screenResolutionHeight = _config->screenResolution.height;
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    float scaleFactor =  (aspectRatio * (float)floorSpriteHeight)/screenResolutionWidth;

    currentLevelWidth = (float)floorSpriteWidth/ scaleFactor;
    currentlevelHeight = _config->screenResolution.height;
    currentlevelDepth = _config->screenResolution.height * 0.25;

    _entityManager->setLevelParameters(currentLevelWidth, currentlevelHeight, currentlevelDepth);
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("[LEVEL]: Inicializando PJ");

    int screenResolutionWidth = _config->screenResolution.width;
    int screenResolutionHeight = _config->screenResolution.height;
    int amountOfPlayers = IDManager::getInstance().amount();

    int offset = (screenResolutionWidth - _screen->getMargin()) / (amountOfPlayers + 1);
    auto charactersConfigs = _config->gameplay.characters;

    int x,y,z;

    IDManager::getInstance().initIDCounter();
    for (int i = 0; i < amountOfPlayers; i++) {
        int newPlayerID = IDManager::getInstance().getNextId();
        
        x = offset*(i+1);
        y = 0;
        z = screenResolutionHeight*0.15;

        IDManager::getInstance().getNextId();
        auto *player = _entityManager->addPlayer(x,y,z,newPlayerID);
        _screen->setPlayer(player);

    }
    LogManager::logDebug("[LEVEL]: Jugadores inicializados: " + std::to_string(amountOfPlayers));

    _entityManager->addBox(50,0,50);
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("[LEVEL]: Inicializando enemigos");

    int amountOfEnemies = _config->gameplay.npcs.size();

    for (int i = 0; i < _config->gameplay.npcs.size();i++) {
        _entityManager->addEnemy();
    }
    LogManager::logDebug("[LEVEL]: Enemigos inicializados: " + std::to_string(amountOfEnemies));
}

void LevelBuilder::initializeWeapons() {
    LogManager::logDebug("[LEVEL]: Inicializando armas");

    for (int i = 0; i < _config->gameplay.weapons.knife.amount;i++) {
        _entityManager->addKnife();
    }
    LogManager::logDebug("[LEVEL]: Armas inicializadas: " + std::to_string(_config->gameplay.weapons.knife.amount));

    for (int i = 0; i < _config->gameplay.weapons.tube.amount;i++) {
        _entityManager->addTube();
    }
    LogManager::logDebug("[LEVEL]: Tubos de metal inicializados: " + std::to_string(_config->gameplay.weapons.tube.amount));
}

void LevelBuilder::initializeUtilities() {
    LogManager::logDebug("[LEVEL]: Inicializando cajas y barriles");

    for (int i = 0; i < _config->gameplay.utilities.box.amount;i++) {
        _entityManager->addBox();
    }
    LogManager::logDebug("[LEVEL]: Cajas inicializadas: " + std::to_string(_config->gameplay.utilities.box.amount));

    for (int i = 0; i < _config->gameplay.utilities.barrel.amount;i++) {
        _entityManager->addBarrel();
    }
    LogManager::logDebug("[LEVEL]: Barriles inicializados: " + std::to_string(_config->gameplay.utilities.barrel.amount));
}

void LevelBuilder::resetPlayers() {
    LogManager::logDebug("[LEVEL]: reseteando jugadores");

    int screenResolutionWidth = _config->screenResolution.width;
    int screenResolutionHeight = _config->screenResolution.height;
    int amountOfPlayers = _entityManager->getPlayers().size();
    int offset = screenResolutionWidth/(amountOfPlayers+1);

    int x, y, z;
    int i = 0;
    for (Character* player : _entityManager->getPlayers()) {

        x = offset*(i+1);
        y = 0;
        z = screenResolutionHeight*0.15;

        player->setPosition(x,y,z);
        i++;
    }
    LogManager::logDebug("[LEVEL]: Jugadores preparados para siguiente nivel: " + std::to_string(amountOfPlayers));
}

void LevelBuilder::resetCamera() {
    LogManager::logDebug("[LEVEL]: reseteando Camara");
    _screen->reset(currentLevelWidth);
}

LevelBuilder::~LevelBuilder(){
    delete(_entityManager);
}
