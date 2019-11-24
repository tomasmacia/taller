//
// Created by axel on 24/11/19.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H


#include "../net/messaging/Sendable.h"
#include "Life.h"
#include "Score.h"
#include "components/Damage.h"

class Character {

public:
    Character(CharacterSendableGenerator* sendableGenerator);
    ~Character();

    void update();
    Sendable* generateSendable();

    Life* getLife(){
        return life;
    }

    Score* getScore(){
        return score;
    }

    Damage* getDamage(){
        return damage;
    }

private:
    Life* life = nullptr;
    Score* score = nullptr;
    Damage* damage = nullptr;

    ID id = nullptr;
    Will will = nullptr;
    State state = nullptr;
    ColitionHandler colitionHandler = nullptr;
    Position position = nullptr;
    Physics physics = nullptr;
    Appearance appearance = nullptr;
    Sound sound = nullptr;

    SendableGenerator sendableGenerator = nullptr;
};
#endif //GAME_CHARACTER_H
