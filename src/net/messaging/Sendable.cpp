//
// Created by axel on 24/11/19.
//

#include "Sendable.h"

Sendable::Sendable(Renderable *renderable, Soundable *soundable) {
    _renderable = renderable;
    _soundable = soundable;
}

Sendable::~Sendable() {

    if (_renderable != nullptr){

        delete(_renderable);
        _renderable = nullptr;
    }

    if (_soundable != nullptr){

        delete(_soundable);
        _soundable = nullptr;
    }

}

bool Sendable::hasRenderable() {
    return _renderable != nullptr;
}

bool Sendable::hasSoundable() {
    return _soundable != nullptr;
}
