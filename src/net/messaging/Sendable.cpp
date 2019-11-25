//
// Created by axel on 24/11/19.
//

#include "Sendable.h"

Sendable::Sendable(Renderable *renderable, Soundable *soundable) {
    _renderable = renderable;
    _soundable = soundable;
}

Sendable::~Sendable() {
    delete(_renderable);
    delete(_soundable);
}
