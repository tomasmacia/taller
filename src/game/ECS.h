//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_ECS_H
#define GAME_ECS_H

#include <bitset>
#include <array>
#include <vector>
#include <memory>
#include <cassert>


class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID getUniqueComponentID() noexcept {
    static ComponentID lastID{0u};
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must inherit from Component");

    static ComponentID typeID{getUniqueComponentID()};
    return typeID;
}

constexpr std::size_t maxComponents{32};

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
    Entity* entity;

    virtual void init() {}

    virtual void update() {}
    virtual void render() {}

    virtual ~Component() {}
};

class Entity {
private:
    bool alive = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitset componentBitset;

public:
    void update() {
        for(auto& c : components) c->update();
    }
    void render() {
        for(auto& c : components) c->render();
    }

    bool isAlive() const { return alive; }
    void destroy() { alive = false; }

    template <typename T>
    bool hasComponent() const {
        return componentBitset[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        assert(!hasComponent<T>());

        T* c = new T(std::forward<TArgs>(mArgs)...);
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->init();

        return *c;
    }

    template <typename T>
    T& getComponent() const {
        assert(hasComponent<T>());
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

#endif //GAME_ECS_H
