//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_ANIMATEDAPPEARANCE_H
#define GAME_ANIMATEDAPPEARANCE_H


#include "StateDrivenAppearance.h"
#include "../../../XMLparser/config/EntityConfig.h"

class AnimatedAppearance : public StateDrivenAppearance{

public:
    AnimatedAppearance(ScreenPosition* screenPosition, State* state, EntityConfig entityConfig);

    void handleCurrentState() override ;

protected:
    EntityConfig entityConfig;

    int STAND_IMAGE_AMOUNT;
    int WALK_IMAGE_AMOUNT;
    int JUMP_IMAGE_AMOUNT;
    int PUNCH_IMAGE_AMOUNT;
    int CROUCH_IMAGE_AMOUNT;
    int KICK_IMAGE_AMOUNT;
    int JUMP_KICK_IMAGE_AMOUNT;
    int PICK_IMAGE_AMOUNT;
    int BEING_ATTACKED_IMAGE_AMOUNT;
    int DYING_IMAGE_AMOUNT;

    Action previous = NONE;
};


#endif //GAME_ANIMATEDAPPEARANCE_H
