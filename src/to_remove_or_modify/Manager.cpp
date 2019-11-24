
#include "Manager.h"

#include "../game/Components/PositionComponent.h"
#include "../logger/LogManager.h"
#include "../game/Components/Appearences/BackgroundRenderComponent.h"
#include "../game/Components/Appearences/NonMobileRenderComponent.h"
#include "../game/Components/Appearences/CharacterRenderComponent.h"
#include "../game/Components/Appearences/NPCRenderComponent.h"
#include "../game/Components/IDComponent.h"
#include "../game/Components/StateComponent.h"

//CONSTRUCTOR
//=========================================================================================
Manager::Manager(){
    packagesToClients = new list<ToClientPack*>;
}

//API
//=========================================================================================
void Manager::update() {//se updatean todas seguro porque updateo las listas que formaban una particion de las entities

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : entitiesWithPosition) e->update();
    for(auto* e : fronLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();
}

std::list<ToClientPack*>* Manager::generateRenderables() {

    for (auto package: *packagesToClients){
        delete package;
        package = nullptr;
    }
    packagesToClients->clear();

    sortEntitiesByY(); //sorteo aca porque es al render al que le importa el orden en la lista

    for(auto* e : backLayerBackgrounds){
        renderable = e->getComponent<BackgroundRenderComponent>()->emitRenderable();

        if (renderable != nullptr && renderable->getPath() != "NULL"){
            packagesToClients->push_back(renderable);
        }
    }

    for(auto* e : entitiesWithPosition){

        if (e->hasComponent<NonMobileRenderComponent>()){
            renderable = e->getComponent<NonMobileRenderComponent>()->emitRenderable();
        }

        if (e->hasComponent<NPCRenderComponent>()){
            renderable = e->getComponent<NPCRenderComponent>()->emitRenderable();
        }

        if (e->hasComponent<CharacterRenderComponent>()){
            renderable = e->getComponent<CharacterRenderComponent>()->emitRenderable();
        }

        if (renderable != nullptr && renderable->getPath() != "NULL"){
            packagesToClients->push_back(renderable);
        }
    }

    for(auto* e : fronLayerBackgrounds){
        renderable = e->getComponent<BackgroundRenderComponent>()->emitRenderable();
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
        if (player->getComponent<IDComponent>()->getId() == id){
            player->getComponent<StateComponent>()->setConnected();
            player->getComponent<CharacterRenderComponent>()->setConnected();
            player->getComponent<IDComponent>()->setNewID(newID);
        }
    }
}

void Manager::disconectPlayerByID(int id){
    for (auto player : players){
        if (player->getComponent<IDComponent>()->getId() == id){
            player->getComponent<StateComponent>()->setDisconnected();
            player->getComponent<CharacterRenderComponent>()->setDisconnected();
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
        int entity1Y = entity1->getComponent<PositionComponent>()->getY();
        int entity2Y = entity2->getComponent<PositionComponent>()->getY();

        if(entity1Y == entity2Y)
            return true;
        return entity1Y < entity2Y;
    }
};

void Manager::sortEntitiesByY() {
    entitiesWithPosition.sort(EntityComparator());
}
