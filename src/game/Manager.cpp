
#include "Manager.h"

#include "PositionComponent.h"
#include "../LogLib/LogManager.h"
#include "BackgroundRenderComponent.h"
#include "NonMobileRenderComponent.h"
#include "CharacterRenderComponent.h"
#include "NPCRenderComponent.h"

//API
//=========================================================================================
void Manager::update() {//se updatean todas seguro porque updateo las listas que formaban una particion de las entities
    sortEntitiesByY();

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : entitiesWithPosition) e->update();
    for(auto* e : fronLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();
}

std::list<ToClientPack>* Manager::generateRenderables() {
    //Estoy al tanto de que overall no es la mejor implementacion posible
    //pero dentro del tiempo que tenemos es la mas elegante que se me ocurre sin hacer cambios estructurales profundos

    std::list<ToClientPack>* packages = new list<ToClientPack>;

    for(auto* e : backLayerBackgrounds){
        ToClientPack renderable = e->getComponent<BackgroundRenderComponent>()->emitRenderable();
        if (renderable.getPath() != "NULL"){
            packages->push_back(renderable);
        }
    }
    for(auto* e : nonMobileEntities){
        ToClientPack renderable = e->getComponent<NonMobileRenderComponent>()->emitRenderable();
        if (renderable.getPath() != "NULL"){
            packages->push_back(renderable);
        }
    }
    for(auto* e : npcs){
        ToClientPack renderable = e->getComponent<NPCRenderComponent>()->emitRenderable();
        if (renderable.getPath() != "NULL"){
            packages->push_back(renderable);
        }
    }
    for(auto* e : players){
        ToClientPack renderable = e->getComponent<CharacterRenderComponent>()->emitRenderable();
        if (renderable.getPath() != "NULL"){
            packages->push_back(renderable);
        }
    }
    for(auto* e : fronLayerBackgrounds){
        ToClientPack renderable = e->getComponent<BackgroundRenderComponent>()->emitRenderable();
        if (renderable.getPath() != "NULL"){
            packages->push_back(renderable);
        }
    }
    return packages;
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
