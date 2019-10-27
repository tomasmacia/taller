
#include "Manager.h"

void Manager::update() {
    for(auto& e : entities) e->update();
}
void Manager::render() {
    for(auto& e : entities) e->render();
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

Entity* Manager::addEntity() {
    auto *e = new Entity();
    entities.push_back(e);
    return e;
}

Entity* Manager::addNonPersistentEntity() {
    auto *e = addEntity();
    nonLevelPersistentEntities.push_back(e);
    return e;
}

Entity* Manager::addBackground() {
    auto *e = addNonPersistentEntity();
    backgrounds.push_back(e);
    return e;
}

Entity* Manager::addPlayer() {
    auto *e = addEntity();
    players.push_back(e);
    return e;
}

Entity* Manager::addCustomEntity(Entity* e) { // in case we want to add behaviour in a custom Entity that inherits from Entity
    nonLevelPersistentEntities.push_back(e);
    return e;
}

void Manager::destroyAllEntities() {for(auto& e : entities) delete(&e);}

void Manager::destroyNonLevelPersistentEntities() {for(auto& e : nonLevelPersistentEntities) delete(&e);}

std::list<Entity*> Manager::getPlayers() {
    return players;
}