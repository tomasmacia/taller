//
// Created by axel on 24/11/19.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "../net/messaging/Sendable.h"
#include "components/Damage.h"
#include "components/Physics.h"
#include "components/InputPoller.h"
#include "components/ScreenPosition.h"
#include "components/appearances/CharacterAppearance.h"
#include "Life.h"
#include "Score.h"
#include "Screen.h"

class Character : public PositionalEntity{

public:
    Character(int x, int y, int z, int w, int h, int id, int walkingSpeed,  const CharacterXML& characterConfig,
                InputPoller* inputPoller, Screen* screen, CollitionManager* collitionManager);
    ~Character();

    //API
    //===============================
    void update() override ;
    Sendable* generateSendable() override;

    void drag();

    void setConnected(int newID);
    void setDisconnected();
    bool isDisconnected();

    int getID();

    //GETTERS
    //===============================
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
    ScreenPosition* screenPosition = nullptr;
    CharacterAppearance* appearance = nullptr;
    Sound* sound = nullptr;
};
#endif //GAME_CHARACTER_H
