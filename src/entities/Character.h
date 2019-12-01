//
// Created by axel on 24/11/19.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "entityHierarchy/AnimatedEntity.h"
#include "components/ID.h"
#include "Score.h"

class Character : public AnimatedEntity{

public:
    Character(Will* will, State* state, AnimatedEntityCollitionHandler* collitionHandler,
              Position* position, Physics* physics, ScreenPosition* screenPosition,
              StateDrivenAppearance* appearance, Sound* sound, Damage* damage,
              Life* life, ID* id, Score* score, ScoreAppearance* scoreAppearance)
    ~Character();

    //API
    //===============================
    void setConnected(int newID);
    void setDisconnected();
    bool isDisconnected();

    int getID();

    //GETTERS
    //===============================
    Score* getScore(){
        return score;
    }

private:
    ID* id = nullptr;
    Score* score = nullptr;
    ScoreAppearance* scoreAppearance = nullptr;
};
#endif //GAME_CHARACTER_H
