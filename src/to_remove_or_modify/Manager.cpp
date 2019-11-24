
#include "Manager.h"

#include "../entities/components/Position.h"
#include "../logger/LogManager.h"
#include "../entities/components/appearances/BackgroundAppearance.h"
#include "../entities/components/appearances/NonMobileAppearance.h"
#include "../entities/components/appearances/CharacterAppearance.h"
#include "../entities/components/appearances/NPCAppearance.h"
#include "../entities/components/ID.h"
#include "../entities/components/ID.h"
asdasda#include "../entities/components/State.h"

//CONSTRUCTOR
//=========================================================================================
Manager::Manager(){
    packagesToClients = new list<Renderable*>;
}

//API
//=========================================================================================
void Manager::update() {//se updatean todas seguro porque updateo las listas que formaban una particion de las entities

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : entitiesWithPosition) e->update();
    for(auto* e : fronLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();
}

std::list<Renderable*>* Manager::generateRenderables() {

    for (auto package: *packagesToClients){
        delete package;
        package = nullptr;
    }
    packagesToClients->clear();

    sortEntitiesByY(); //sorteo aca porque es al render al que le importa el orden en la lista

    for(auto* e : backLayerBackgrounds){
        renderable = e->getComponent<BackgroundAppearance>()->emitRenderable();

        if (renderable != nullptr && renderable->getPath() != "NULL"){
            packagesToClients->push_back(renderable);
        }
    }

    for(auto* e : entitiesWithPosition){

        if (e->hasComponent<NonMobileAppearance>()){
            renderable = e->getComponent<NonMobileAppearance>()->emitRenderable();
        }

        if (e->hasComponent<NPCAppearance>()){
            renderable = e->getComponent<NPCAppearance>()->emitRenderable();
        }

        if (e->hasComponent<CharacterAppearance>()){
            renderable = e->getComponent<CharacterAppearance>()->emitRenderable();
        }

        if (renderable != nullptr && renderable->getPath() != "NULL"){
            packagesToClients->push_back(renderable);
        }
    }

    for(auto* e : fronLayerBackgrounds){
        renderable = e->getComponent<BackgroundAppearance>()->emitRenderable();
        if (renderable != nullptr && renderable->getPath() != "NULL"){
            packagesToClients->push_back(renderable);
        }
    }
    renderable = nullptr;

    return packagesToClients;
}

void Manager::prepareForNextLevel(){

    entitiesWithPosition.clear();
    destroyNonLevelPersistentEntities();
    npcs.clear();
    nonMobileEntities.clear();
    backLayerBackgrounds.clear();
    fronLayerBackgrounds.clear();

    for (auto* e : players){
        entitiesWithPosition.push_back(e);
    }
}

void Manager::reconectPlayerByID(int id,  int newID) {
    for (auto player : players){
        if (player->getComponent<ID>()->get() == id){
            player->getComponent<State>()->setConnected();
            player->getComponent<CharacterAppearance>()->setConnected();
            player->getComponent<ID>()->setNew(newID);
        }
    }
}

void Manager::disconectPlayerByID(int id){
    for (auto player : players){
        if (player->getComponent<ID>()->get() == id){
            player->getComponent<State>()->setDisconnected();
            player->getComponent<CharacterAppearance>()->setDisconnected();
        }
    }
}

//ADDING NEW ENTITIES
//=========================================================================================
Entity* Manager::addNPC() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    npcs.push_back(e);
    entitiesWithPosition.push_back(e);
    return e;
}

Entity* Manager::addUtilitie() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    nonMobileEntities.push_back(e);
    entitiesWithPosition.push_back(e);
    return e;
}

Entity* Manager::addWeapon() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    nonMobileEntities.push_back(e);
    entitiesWithPosition.push_back(e);
    return e;
}

Entity* Manager::addPlayer() {
    auto *e = new Entity();
    players.push_back(e);
    entitiesWithPosition.push_back(e);
    return e;
}

Entity* Manager::addBackLayerBackgrounds() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    backLayerBackgrounds.push_back(e);
    return e;
}

Entity* Manager::addFrontLayerBackgrounds() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    fronLayerBackgrounds.push_back(e);
    return e;
}

Entity* Manager::addSpecialEntity() {
    auto *e = new Entity();
    specialEntities.push_back(e);
    return e;
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

    delete renderable;
    renderable = nullptr;
    LogManager::logDebug("Memoria de Manager liberada");
}

//SORTING
//=========================================================================================
struct EntityComparator
{
    bool operator ()(const Entity* entity1, const Entity* entity2)
    {
        int entity1Y = entity1->getComponent<Position>()->getY();
        int entity2Y = entity2->getComponent<Position>()->getY();

        if(entity1Y == entity2Y)
            return true;
        return entity1Y < entity2Y;
    }
};

void Manager::sortEntitiesByY() {
    entitiesWithPosition.sort(EntityComparator());
}
