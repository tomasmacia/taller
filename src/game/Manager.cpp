
#include "Manager.h"

#include "PositionComponent.h"

#include <iostream>

void Manager::update() {
    sortEntitiesByY();

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : entitiesWithPosition) e->update();
    for(auto* e : fronLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();
}
void Manager::render() {

    for(auto* e : backLayerBackgrounds) e->render();
    for(auto* e : entitiesWithPosition) e->render();
    for(auto* e : fronLayerBackgrounds) e->render();
}

Entity* Manager::addNPC() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    entitiesWithPosition.push_back(e);
    return e;
}

Entity* Manager::addUtilitie() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
    entitiesWithPosition.push_back(e);
    return e;
}

Entity* Manager::addWeapon() {
    auto *e = new Entity();
    nonLevelPersistentEntities.push_back(e);
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

Entity* Manager::addCustomEntity(Entity* e) { // in case we want to add behaviour in a custom Entity that inherits from Entity
    nonLevelPersistentEntities.push_back(e);
    return e;
}

void Manager::destroyAllEntities() {
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
void Manager::prepareForNextLevel(){

    entitiesWithPosition.clear();
    destroyNonLevelPersistentEntities();
    backLayerBackgrounds.clear();
    fronLayerBackgrounds.clear();

    for (auto* e : players){
        entitiesWithPosition.push_back(e);
    }
}

std::list<Entity*> Manager::getPlayers() {
    return players;
}

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



/*
void Manager::refresh() {// estas perdiendo el puntero, no estas eliminando al objeto
    entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
                    [](const std::unique_ptr<Entity>& mEntity) {
                        return !mEntity->isAlive();
                    }),
            std::end(entities));
}*/

