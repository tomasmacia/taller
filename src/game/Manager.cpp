
#include "Manager.h"
#include "../logger/LogManager.h"

//CONSTRUCTOR
//=========================================================================================
Manager::Manager(){
    packagesToClients = new list<Sendable*>;
}

//API
//=========================================================================================
void Manager::update() {//se updatean todas seguro porque updateo las listas que formaban una particion de las entities

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : entitiesWithPosition) e->update();
    for(auto* e : fronLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();
}

std::list<Sendable*>* Manager::generateSendables() {

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

void Manager::prepareForNextLevel(){

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

void Manager::reconectPlayerByID(int id,  int newID) {
    for (auto player : players){
        if (player->getID() == id){
            player->setConnected(id);
        }
    }
}

void Manager::disconectPlayerByID(int id){
    for (auto player : players){
        if (player->getID() == id){
            player->setDisconnected();
        }
    }
}

//ADDING NEW ENTITIES
//=========================================================================================
void Manager::addNPC(PositionalEntity* enemy) {
    nonLevelPersistentEntities.push_back(enemy);
    npcs.push_back(enemy);
    entitiesWithPosition.push_back(enemy);
}

void Manager::addUtilitiy(Entity* utillity) {
    nonLevelPersistentEntities.push_back(utillity);
    nonMobileEntities.push_back(utillity);
    entitiesWithPosition.push_back((PositionalEntity*) utillity);
}

void Manager::addWeapon(Entity* weapon) {
    nonLevelPersistentEntities.push_back(weapon);
    nonMobileEntities.push_back(weapon);
    entitiesWithPosition.push_back((PositionalEntity*) weapon);
}

void Manager::addPlayer(PositionalEntity* player) {
    players.push_back((Character*) player);
    entitiesWithPosition.push_back(player);
}

void Manager::addBackLayerBackgrounds(Background* background) {
    nonLevelPersistentEntities.push_back(background);
    backLayerBackgrounds.push_back(background);
}

void Manager::addFrontLayerBackgrounds(Background* background) {
    nonLevelPersistentEntities.push_back(background);
    fronLayerBackgrounds.push_back(background);
}

void Manager::addScreen(Screen* screen) {
    specialEntities.push_back((Entity*) screen);
}

//DESTROY
//=========================================================================================
void Manager::destroyAllEntities() { //se destruyen todas seguro porque borro las listas que formaban una particion de las entities
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

void Manager::destroyNonLevelPersistentEntities() {
    for(auto* e : nonLevelPersistentEntities){
        delete e;
        e = nullptr;
    }
    nonLevelPersistentEntities.clear();
}

Manager::~Manager() {
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
    LogManager::logDebug("Memoria de Manager liberada");
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

void Manager::sortEntitiesByZ() {
    entitiesWithPosition.sort(EntityComparator());
}
