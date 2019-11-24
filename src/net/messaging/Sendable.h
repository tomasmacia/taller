//
// Created by axel on 24/11/19.
//

#ifndef GAME_SENDABLE_H
#define GAME_SENDABLE_H


#include "Renderable.h"
#include "Soundable.h"

class Sendable {

public:
    Soundable* soundable = nullptr;
    Renderable* renderable = nullptr;

    Sendable(Soundable* soundable,Renderable* renderable);
    ~Sendable();
};


#endif //GAME_SENDABLE_H
