//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_UNANIMATEDENTITY_H
#define GAME_UNANIMATEDENTITY_H


#include "PhysicalEntity.h"

class UnanimatedEntity : public PhysicalEntity {

public:
    UnanimatedEntity(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                     State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound, int w, int h, int d);

    bool broke();
};


#endif //GAME_UNANIMATEDENTITY_H
