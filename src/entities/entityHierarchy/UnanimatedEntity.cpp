//
// Created by axel on 28/11/19.
//

#include "UnanimatedEntity.h"


UnanimatedEntity::UnanimatedEntity(State *state, Position *position, ScreenPosition *screenPosition,
                               StateDrivenAppearance *appearance, Damage *damage, Life *life) :

                                PhysicalEntity(state, screenPosition, appearance, position, damage, life, score){
}