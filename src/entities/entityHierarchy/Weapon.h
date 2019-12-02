//
// Created by axel on 28/11/19.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H


#include "UnanimatedEntity.h"

class Weapon : public UnanimatedEntity{

public:
    virtual int useOn(Entity* entity);

protected:
    int USES_AMOUNT = 3;
};



#endif //GAME_WEAPON_H
