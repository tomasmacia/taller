
#include "EntityManager.h"
#include "../logger/LogManager.h"

#include "../entities/components/collition/AnimatedEntityCollitionHandler.h"
#include "../entities/components/InputPoller.h"
#include "../entities/components/State.h"
#include "../entities/components/Position.h"
#include "../entities/components/Physics.h"
#include "../entities/components/ScreenPosition.h"
#include "../entities/components/appearances/CharacterAppearance.h"
#include "../entities/components/Sound.h"
#include "../entities/components/Damage.h"
#include "../entities/Life.h"
#include "../entities/Score.h"
#include "../entities/components/ID.h"
#include "../entities/components/appearances/ScoreAppearance.h"

//CONSTRUCTOR
//=========================================================================================
EntityManager::EntityManager(Controller* controller, Config* config){
    packagesToClients = new list<Sendable*>();
    initializeCollitionManager();

    this->controller = controller;
    this->config = config;
}

void EntityManager::initializeCollitionManager(){
    LogManager::logDebug("[LEVEL]: Inicializando Collition EntityManager");
    collitionManager = new CollitionManager();
}

//API
//=========================================================================================
void EntityManager::update() {//se updatean todas seguro porque updateo las listas que formaban una particion de las entities

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : entitiesWithPosition) e->update();
    for(auto* e : fronLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();
}

std::list<Sendable*>* EntityManager::generateSendables() {

    for (auto package: *packagesToClients){
        delete package;
        package = nullptr;
    }
    packagesToClients->clear();

    sortEntitiesByZ(); //sorteo aca porque es al render al que le importa el orden en la lista

    for(auto* e : backLayerBackgrounds){
        sendable = e->generateSendable();
        if (sendable != nullptr){
            packagesToClients->push_back(sendable);
        }
    }

    for(auto* e : entitiesWithPosition){
        sendable = e->generateSendable();
        if (sendable != nullptr){
            packagesToClients->push_back(sendable);
        }
    }

    for(auto* e : fronLayerBackgrounds){
        sendable = e->generateSendable();
        if (sendable != nullptr){
            packagesToClients->push_back(sendable);
        }
    }
    sendable = nullptr;

    return packagesToClients;
}

void EntityManager::prepareForNextLevel(){

    collitionManager->prepareForNextLevel();
    entitiesWithPosition.clear();
    destroyNonLevelPersistentEntities();
    enemies.clear();
    inanimatedEntities.clear();
    backLayerBackgrounds.clear();
    fronLayerBackgrounds.clear();

    for (Character* e : players){
        entitiesWithPosition.push_back(e);
    }
}

void EntityManager::reconectPlayerByID(int id, int newID) {
    for (auto player : players){
        if (player->getID() == id){
            player->setConnected(id);
        }
    }
}

void EntityManager::disconectPlayerByID(int id){
    for (auto player : players){
        if (player->getID() == id){
            player->setDisconnected();
        }
    }
}

//ADDING NEW ENTITIES
//=========================================================================================
Character* EntityManager::addPlayer(int x, int y, int z, int w, int h, int id, int walkingSpeed) {
    Character* character = createCharacter(x,y,z,w,h,id,walkingSpeed);
    players.push_back(character);
    entitiesWithPosition.push_back(character);
}

void EntityManager::addEnemy(int w, int h, int walkingSpeed) {
    Enemy* enemy = createEnemy(w,h,walkingSpeed);
    nonLevelPersistentEntities.push_back(enemy);
    enemies.push_back(enemy);
    entitiesWithPosition.push_back(enemy);
}

void EntityManager::addKnife(int w, int h) {
    auto* knife = createKnife(w,h);
    nonLevelPersistentEntities.push_back(knife);
    inanimatedEntities.push_back(knife);
    entitiesWithPosition.push_back(knife);
}

void EntityManager::addTube(int w, int h) {
    auto* tube = createTube(w,h);
    nonLevelPersistentEntities.push_back(tube);
    inanimatedEntities.push_back(tube);
    entitiesWithPosition.push_back(tube);
}

void EntityManager::addBox(int w, int h) {
    auto* box = createBox(w,h);
    nonLevelPersistentEntities.push_back(box);
    inanimatedEntities.push_back(box);
    entitiesWithPosition.push_back(box);
}

void EntityManager::addBarrel(int w, int h) {
    auto* barrel = createBarrel(w,h);
    nonLevelPersistentEntities.push_back(barrel);
    inanimatedEntities.push_back(barrel);
    entitiesWithPosition.push_back(barrel);
}

void EntityManager::addBackLayerBackgrounds(Background* background) {
    nonLevelPersistentEntities.push_back(background);
    backLayerBackgrounds.push_back(background);
}

void EntityManager::addFrontLayerBackgrounds(Background* background) {
    nonLevelPersistentEntities.push_back(background);
    fronLayerBackgrounds.push_back(background);
}

Screen* EntityManager::addScreen(int screenWidth, int screenHeight, int levelWidth) {
    screen = new Screen(screenWidth, screenHeight, levelWidth, collitionManager);
    specialEntities.push_back((Entity*) screen);
    return screen;
}

//ADDING NEW ENTITIES
//=========================================================================================
Character *EntityManager::createCharacter(int x, int y, int z, int w, int h, int id, int walkingSpeed) {

    auto* idComponent = new ID(id);
    auto* will = new InputPoller(controller, idComponent);
    auto* state = new State(will);

    auto* punchBox = new CollitionBox(x, y, z, w, h, -1,-1);
    auto* kickBox = new CollitionBox(x, y, z, w, h, -1,-1);
    auto* collitionBox = collitionManager->addCharacterBlockingCollitionBox(x, y, z, w, h, -1);
    auto* collitionHandler = new AnimatedEntityCollitionHandler(punchBox, kickBox, collitionBox, collitionManager, state);

    auto* position = new Position(x, y, z, collitionHandler);
    auto* physics = new Physics(state,position,walkingSpeed);
    auto* screenPosition = new ScreenPosition(position,screen);
    auto* appearance = new CharacterAppearance(w, h, screenPosition, state, config->gameplay.characters.at(players.size()));
    auto* sound = new Sound(state);
    auto* damage = new Damage(state);
    auto* life = new Life(state);
    auto* score = new Score();
    auto* scoreAppearance = new ScoreAppearance(score);

    return new Character(will, state, collitionHandler, position, physics, screenPosition,
                         appearance, sound, damage,life, idComponent, score, scoreAppearance);
}

Enemy *EntityManager::createEnemy(int w, int h, int walkingSpeed) {

    auto* will = new IA();
    auto* state = new State(will);

    auto* punchBox = new CollitionBox(x, y, z, w, h, -1,-1);
    auto* kickBox = new CollitionBox(x, y, z, w, h, -1,-1);
    auto* collitionBox = collitionManager->addBlockingCollitionBox(x, y, z, w, h, -1);
    auto* collitionHandler = new AnimatedEntityCollitionHandler(punchBox, kickBox, collitionBox, collitionManager, state);

    auto* position = new Position(x, y, z, collitionHandler);
    auto* physics = new Physics(state,position,walkingSpeed);
    auto* screenPosition = new ScreenPosition(position,screen);
    auto* appearance = new EnemyAppearance(w, h, screenPosition, state, config->gameplay.characters.at(players.size()));
    auto* sound = new Sound(state);
    auto* damage = new Damage(state);
    auto* life = new Life(state);
    auto* score = new Score();

    return new Enemy(will, state, collitionHandler, position, physics, screenPosition,
                         appearance, sound, damage,life, score);
}


Knife* EntityManager::createKnife(int w, int h) {

}

Tube* EntityManager::createTube(int w, int h) {

}

Box* EntityManager::createBox(int w, int h) {

}

Barrel* EntityManager::createBarrel(int w, int h) {

}

Background* EntityManager::createFar() {

}

Background* EntityManager::createMiddle() {

}

Background* EntityManager::createFloor() {

}

Background* EntityManager::createOverlay() {

}

//DESTROY
//=========================================================================================
void EntityManager::destroyAllEntities() { //se destruyen todas seguro porque borro las listas que formaban una particion de las entities
    for(auto* e : entitiesWithPosition) {
        delete e;
        e = nullptr;
    }
    for(auto* e : specialEntities){
        delete e;
        e = nullptr;
    }
    for(auto* e : backLayerBackgrounds) {
        delete e;
        e = nullptr;
    }
    for(auto* e : fronLayerBackgrounds) {
        delete e;
        e = nullptr;
    }
}

void EntityManager::destroyNonLevelPersistentEntities() {
    for(auto* e : nonLevelPersistentEntities){
        delete e;
        e = nullptr;
    }
    nonLevelPersistentEntities.clear();
}

EntityManager::~EntityManager() {
    destroyAllEntities();
    entitiesWithPosition.clear();
    enemies.clear();
    inanimatedEntities.clear();
    specialEntities.clear();
    nonLevelPersistentEntities.clear();
    players.clear();
    backLayerBackgrounds.clear();
    fronLayerBackgrounds.clear();

    for (auto package: *packagesToClients){
        delete package;
    }
    packagesToClients->clear();
    delete packagesToClients;
    packagesToClients = nullptr;

    delete sendable;
    sendable = nullptr;
    delete collitionManager;
    collitionManager = nullptr;

    LogManager::logDebug("Memoria de EntityManager liberada");
}

//SORTING
//=========================================================================================
struct EntityComparator
{
    bool operator ()(PositionalEntity* entity1, PositionalEntity* entity2)
    {
        int entity1Z = entity1->getZ();
        int entity2Z = entity2->getZ();

        if(entity1Z == entity2Z)
            return true;
        return entity1Z < entity2Z;
    }
};

void EntityManager::sortEntitiesByZ() {
    entitiesWithPosition.sort(EntityComparator());
}