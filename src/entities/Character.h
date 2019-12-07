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
    Character(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
              State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
              Will* will, Physics* physics, Attack* attack, ID* id, ScoreAppearance* scoreAppearance);

    ~Character();

    //API
    //===============================
    list<Sendable*> generateSendable() override;

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
    int AMOUNT_OF_LIFES_CHARACTER = 3;
    int CHARACTER_LIFE_AMOUNT = 100;

    ID* id = nullptr;
    ScoreAppearance* scoreAppearance = nullptr;
};
#endif //GAME_CHARACTER_H
