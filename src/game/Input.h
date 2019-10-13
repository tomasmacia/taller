#ifndef GAME_INPUT_H
#define GAME_INPUT_HGAME_PHYSICSCOMPONENT_H

#include "character.h"

class Input {

private:

public:
    Input();
    ~Input();

    virtual void activate(Character* character) = 0;
};

#endif //GAME_INPUT_H