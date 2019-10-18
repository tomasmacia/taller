//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H


#include <vector>
#include <memory>
#include <algorithm>

#include "ECS.h"

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update() {
        for(auto& e : entities) e->update();
    }
    void render() {
        for(auto& e : entities) e->render();
    }

    void refresh() {
        entities.erase(
                std::remove_if(std::begin(entities), std::end(entities),
                        [](const std::unique_ptr<Entity>& mEntity) {
                            return !mEntity->isAlive();
                        }),
                std::end(entities));
    }

    Entity* addEntity() {
        auto *e = new Entity();
        entities.push_back(std::unique_ptr<Entity>(e));
        return e;
    }

    Entity& addCustomEntity(Entity* e) { // in case we want to add behaviour in a custom Entity that inherits from Entity
        entities.push_back(std::unique_ptr<Entity>(e));
        return *e;
    }

    void destroyAllEntities() {
        entities.clear();
    }
};


#endif //GAME_MANAGER_H
