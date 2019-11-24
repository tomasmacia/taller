//
// Created by axel on 24/11/19.
//

#include "Sendable.h"

Sendable::Sendable(Soundable* soundable,Renderable* renderable){
    this->soundable = soundable;
    this->renderable = renderable;
}

Sendable::~Sendable(){
    delete(soundable);
    delete(renderable);
}