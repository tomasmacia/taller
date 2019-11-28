//
// Created by axel on 28/11/19.
//

#ifndef GAME_POSITIONALENTITY_H
#define GAME_POSITIONALENTITY_H

#include "Entity.h"
#include "../components/Position.h"

class PositionalEntity : public Entity{

public:
    PositionalEntity(Position *position);

    int getX();
    int getY();
    int getZ();

protected:
    Position* position = nullptr;

};


#endif //GAME_POSITIONALENTITY_H
