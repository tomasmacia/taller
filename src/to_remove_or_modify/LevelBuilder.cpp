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

    initializeLevelWidth();
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

    initializeLevelWidth();
    resetCamera();
    initializeWorld();
    resetPlayers();
    initializeEnemies();
    initializeWeapons();
    initializeUtilities();
}

void LevelBuilder::initializeCamera() {
    LogManager::logDebug("[LEVEL]: Inicializando Camara");
    _screen = _entityManager->addScreen(_config->screenResolution.width, _config->screenResolution.height, currentLevelWidth);
}

void LevelBuilder::initializeWorld() {
    LogManager::logDebug("[LEVEL]: Inicializando Fondos");

    Level currentLevelSprites = _config->gameplay.levels.at(currentLevel - 1);

    if (!currentLevelSprites.far.empty()){

        string stritePath = currentLevelSprites.far.front();
        auto *far = new Background(_screen, stritePath, FAR_SPEED_RATIO, nullptr);
        _entityManager->addBackLayerBackgrounds(far);
    }

    if (!currentLevelSprites.middle.empty()){

        string stritePath = currentLevelSprites.middle.front();
        auto *middle = new Background(_screen, stritePath, MIDDLE_SPEED_RATIO, _collitionManager, nullptr);
        _entityManager->addBackLayerBackgrounds(middle);
    }

    if (!currentLevelSprites.floor.empty()){

        string stritePath = currentLevelSprites.floor.front();
        auto *floor = new Background(_screen, stritePath, FLOOR_SPEED_RATIO, _collitionManager, nullptr);
        _entityManager->addBackLayerBackgrounds(floor);
    }

    if (!currentLevelSprites.overlay.empty()){

        string stritePath = currentLevelSprites.overlay.front();
        auto *overlay = new Background(_screen, stritePath, OVERLAY_SPEED_RATIO, _collitionManager, nullptr);
        _entityManager->addBackLayerBackgrounds(overlay);
    }
    LogManager::logDebug("[LEVEL]: Fondos inicializados");
}

void LevelBuilder::initializeLevelWidth(){

    std::string floorSpritePath = _config->gameplay.levels.at(currentLevel).floor.front();

    ImageSize imageSize = ImageUtils::getImageSize(floorSpritePath);
    int floorSpriteWidth = imageSize.width;
    int floorSpriteHeight = imageSize.height;

    int screenResolutionWidth = _config->screenResolution.width;
    int screenResolutionHeight = _config->screenResolution.height;
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    float scaleFactor =  (aspectRatio * (float)floorSpriteHeight)/screenResolutionWidth;

    currentLevelWidth = (float)floorSpriteWidth/ scaleFactor;
}

void LevelBuilder::initializePlayers() {
    LogManager::logDebug("[LEVEL]: Inicializando PJ");

    int screenResolutionWidth = _config->screenResolution.width;
    int screenResolutionHeight = _config->screenResolution.height;
    int amountOfPlayers = _config->gameplay.characters.size();

    int offset = (screenResolutionWidth - _screen->getMargin()) / (amountOfPlayers + 1);
    auto charactersConfigs = _config->gameplay.characters;

    int x,y,z,w,h,walkingSpeed;



    int i = 0;
    IDManager::getInstance().initIDCounter();
    for (int i = 0; i < amountOfPlayers; i++) {
        int newPlayerID = IDManager::getInstance().getNextId();
        
        x = offset*(i+1);
        y = 0;
        z = screenResolutionHeight/2;

        IDManager::getInstance().getNextId();
        auto *player = _entityManager->addPlayer(x,y,z,w,h,newPlayerID,walkingSpeed);
        _screen->setPlayer(player);

    }
    LogManager::logDebug("[LEVEL]: Jugadores inicializados: " + std::to_string(amountOfPlayers));
}

void LevelBuilder::initializeEnemies() {
    LogManager::logDebug("[LEVEL]: Inicializando enemigos");

    int amountOfEnemies = _config->gameplay.npcs.size();
    int w,h,walkingSpeed;



    for (int i = 0; i < _config->gameplay.npcs.size();i++) {
        _entityManager->addEnemy(w,h,walkingSpeed);
    }
    LogManager::logDebug("[LEVEL]: Enemigos inicializados: " + std::to_string(amountOfEnemies));
}

void LevelBuilder::initializeWeapons() {
    LogManager::logDebug("[LEVEL]: Inicializando armas");

    int knifeWidth, knifeHeight;

    for (int i = 0; i < _config->gameplay.weapons.knife.amount;i++) {
        _entityManager->addWeapon(knifeWidth,knifeHeight);
    }
    LogManager::logDebug("[LEVEL]: Armas inicializadas: " + std::to_string(_config->gameplay.weapons.knife.amount));

    int tubeWidth, tubeHeight;


    for (int i = 0; i < _config->gameplay.weapons.tube.amount;i++) {
        _entityManager->addWeapon(tubeWidth,tubeHeight);
    }
    LogManager::logDebug("[LEVEL]: Tubos de metal inicializados: " + std::to_string(_config->gameplay.weapons.tube.amount));
}

void LevelBuilder::initializeUtilities() {
    LogManager::logDebug("[LEVEL]: Inicializando cajas y barriles");

    int boxWidth, boxHeight;

    for (int i = 0; i < _config->gameplay.utilities.box.amount;i++) {
        _entityManager->addUtilitiy(boxWidth, boxHeight);
    }
    LogManager::logDebug("[LEVEL]: Cajas inicializadas: " + std::to_string(_config->gameplay.utilities.box.amount));

    int barrelWidth, barrrelHeight;


    for (int i = 0; i < _config->gameplay.utilities.barrel.amount;i++) {
        _entityManager->addUtilitiy(barrelWidth, barrrelHeight);
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
        z = screenResolutionHeight/2;

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
