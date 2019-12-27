//
// Created by axelmpm on 3/12/19.
//

#ifndef GAME_NULLWILL_H
#define GAME_NULLWILL_H


#include "Will.h"

class NullWill : public Will{

public:
    void update() override {}
    Action getNext() override;

    ~NullWill() override {

    };
};


#endif //GAME_NULLWILL_H
