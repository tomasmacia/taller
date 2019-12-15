//
// Created by axel on 24/11/19.
//

#ifndef GAME_SENDABLE_H
#define GAME_SENDABLE_H

#include <string>
#include "Renderable.h"
#include "Soundable.h"
using namespace std;

class Sendable {

public:
    Sendable(Renderable* renderable, Soundable* soundable);
    ~Sendable();

    Renderable* _renderable = nullptr;
    Soundable* _soundable = nullptr;

    bool hasRenderable();

    bool hasSoundable();
};


#endif //GAME_SENDABLE_H
