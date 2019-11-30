
#include "EntityManager.h"
#include "../logger/LogManager.h"

//CONSTRUCTOR
//=========================================================================================
EntityManager::EntityManager(){
    packagesToClients = new list<Sendable*>;
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

    entitiesWithPosition.clear();
    destroyNonLevelPersistentEntities();
    npcs.clear();
    nonMobileEntities.clear();
    backLayerBackgrounds.clear();
    fronLayerBackgrounds.clear();

    for (Character* e : players){
        entitiesWithPosition.push_back((PositionalEntity*) e);
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
void EntityManager::addNPC(PositionalEntity* enemy) {
    nonLevelPersistentEntities.push_back(enemy);
    npcs.push_back(enemy);
    entitiesWithPosition.push_back(enemy);
}

void EntityManager::addUtilitiy(Entity* utillity) {
    nonLevelPersistentEntities.push_back(utillity);
    nonMobileEntities.push_back(utillity);
    entitiesWithPosition.push_back((PositionalEntity*) utillity);
}

void EntityManager::addWeapon(Entity* weapon) {
    nonLevelPersistentEntities.push_back(weapon);
    nonMobileEntities.push_back(weapon);
    entitiesWithPosition.push_back((PositionalEntity*) weapon);
}

void EntityManager::addPlayer(PositionalEntity* player) {
    players.push_back((Character*) player);
    entitiesWithPosition.push_back(player);
}

void EntityManager::addBackLayerBackgrounds(Background* background) {
    nonLevelPersistentEntities.push_back(background);
    backLayerBackgrounds.push_back(background);
}

void EntityManager::addFrontLayerBackgrounds(Background* background) {
    nonLevelPersistentEntities.push_back(background);
    fronLayerBackgrounds.push_back(background);
}

void EntityManager::addScreen(Screen* screen) {
    specialEntities.push_back((Entity*) screen);
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
    npcs.clear();
    nonMobileEntities.clear();
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
