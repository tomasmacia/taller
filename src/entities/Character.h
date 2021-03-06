//
// Created by axel on 24/11/19.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "entityHierarchy/AnimatedEntity.h"
#include "components/ID.h"
#include "Score.h"
#include "components/appearances/ScoreAppearance.h"
#include "components/InputPoller.h"

class Character : public AnimatedEntity{

public:
    Character(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
              State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
              Will* will, Physics* physics, Attack* attack, ID* id, ScoreAppearance* scoreAppearance, int w, int h, int d);

    ~Character();

    //API
    //===============================
    list<Sendable*> generateSendable() override;
    list<Sendable *> generateScoreAndLifeSendable();

    int setAttackedWith(AttackCode attackCode) override;
    void notifySuccessfulAttack(int score) override;

    void setConnected(int newID);
    void setDisconnected();
    bool isDisconnected();
    void setPositionYToScore(int a);
    void setPositionXToScore(int a);
    void setPositionYToLife(int a);
    void setPositionXToLife(int a);
    void setColorLifeBar(int a);
    void setAction(Action action);

    void removeWeapon();

    int getID();
    int getScore();

    bool isCharacter() override {return true;}

    //GETTERS
    //===============================
    ScoreAppearance* getScoreAppearance(){
        return scoreAppearance;
    }

    LifeAppearance* getLifeAppearance(){
        return life->getAppearance();
    }

    void resetAt(int x, int y, int z);

    void setTestMode();

    void removeTestMode();

    void turnToDead();

    bool turnedToDead();

    int getAcumulatedScore();

private:
    int AMOUNT_OF_LIFES_CHARACTER = 3;
    int CHARACTER_LIFE_AMOUNT = 100;

    bool markedAsDead = false;

    ID* id = nullptr;
    ScoreAppearance* scoreAppearance = nullptr;
    InputPoller* inputPoller = nullptr;
};
#endif //GAME_CHARACTER_H
