//
// Created by axel on 24/11/19.
//

#ifndef GAME_WILL_H
#define GAME_WILL_H


#include "../../enumerates/Action.h"

class Will {

public:
    virtual void update() = 0;

    virtual Action getNext() = 0;
};


#endif //GAME_WILL_H
