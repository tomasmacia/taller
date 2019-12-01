//
// Created by axel on 28/11/19.
//

#ifndef GAME_UTILLITY_H
#define GAME_UTILLITY_H


#include "InanimatedEntity.h"
#include "../Life.h"

class Utillity : public InanimatedEntity{

public:
    Utillity(Life* life);

    bool broke();

private:
    Life* life = nullptr;
};


#endif //GAME_UTILLITY_H
