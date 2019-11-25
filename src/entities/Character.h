//
// Created by axel on 24/11/19.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "../net/messaging/Sendable.h"
#include "components/Damage.h"
#include "components/Physics.h"
#include "components/InputPoller.h"
#include "components/appearances/CharacterAppearance.h"
#include "Life.h"
#include "Score.h"
#include "Screen.h"

class Character {

public:
    Character(int x, int y, int z, int w, int h, int walkingSpeed,  const CharacterXML& characterConfig,
                InputPoller* inputPoller, Screen* screen, CollitionManager* collitionManager);
    ~Character();

    void update();
    Sendable* generateSendable();

    void drag();
    bool isDisconnected();
    int getX();

    Life* getLife(){
        return life;
    }

    Score* getScore(){
        return score;
    }

    Damage* getDamage(){
        return damage;
    }

    int getWalkingSpeed(){
        return _wakingSpeed;
    }

private:
    int DEFAULT_DEPH = 5;
    int _wakingSpeed;

    Life* life = nullptr;
    Score* score = nullptr;
    Damage* damage = nullptr;

    ID* id = nullptr;
    Will* will = nullptr;
    State* state = nullptr;
    ColitionHandler* collitionHandler = nullptr;
    Position* position = nullptr;
    Physics* physics = nullptr;
    Appearance* appearance = nullptr;
    Sound* sound = nullptr;

    SendableGenerator sendableGenerator = nullptr;
};
#endif //GAME_CHARACTER_H
