//
// Created by axel on 24/11/19.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "entityHierarchy/AnimatedEntity.h"
#include "components/ID.h"
#include "Score.h"
#include "components/appearances/ScoreAppearance.h"

class Character : public AnimatedEntity{

public:
    Character(Will* will, State* state, AnimatedEntityCollitionHandler* collitionHandler,
              Position* position, Physics* physics, ScreenPosition* screenPosition,
              StateDrivenAppearance* appearance, Sound* sound, Damage* damage,
              Life* life, ID* id, Score* score, ScoreAppearance* scoreAppearance);

    ~Character();

    //API
    //===============================
    int setAttackedWith(AttackCode attackCode);
    void notifySuccessfulAttack(int score) override;

    void setConnected(int newID);
    void setDisconnected();
    bool isDisconnected();

    int getID();

    //GETTERS
    //===============================
    ScoreAppearance* getScoreAppearance(){
        return scoreAppearance;
    }

    LifeAppearance* getLifeAppearance(){
        return life->getAppearance();
    }

private:
    ID* id = nullptr;
    ScoreAppearance* scoreAppearance = nullptr;
};
#endif //GAME_CHARACTER_H
