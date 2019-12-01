//
// Created by axel on 28/11/19.
//

#ifndef GAME_UTILLITY_H
#define GAME_UTILLITY_H


#include "UnanimatedEntity.h"
#include "../Life.h"

class Utillity : public UnanimatedEntity{

public:
    Utillity(Life* life);

    bool broke();
};


#endif //GAME_UTILLITY_H
