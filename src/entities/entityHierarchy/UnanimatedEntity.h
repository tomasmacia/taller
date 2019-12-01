//
// Created by axel on 28/11/19.
//

#ifndef GAME_UNANIMATEDENTITY_H
#define GAME_UNANIMATEDENTITY_H

#include "PhysicalEntity.h"

class UnanimatedEntity : public PhysicalEntity {

public:
    UnanimatedEntity(State *state, Position *position, ScreenPosition *screenPosition,
            StateDrivenAppearance *appearance, Damage *damage, Life *life);
};


#endif //GAME_UNANIMATEDENTITY_H
