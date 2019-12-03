//
// Created by axel on 28/11/19.
//

#include "Background.h"

Background::Background(CollitionHandler *collitionHandler, BackgroundAppearance* appearance) : Entity(collitionHandler) {
    this->appearance = appearance;
}

Background::Background(BackgroundAppearance *appearance) {
    this->appearance = appearance;
}

void Background::update() {
    appearance->update();
}

Sendable *Background::generateSendable() {
    auto renderable = appearance->generateRenderable();
    return new Sendable(renderable, nullptr);
}

Background::~Background() {
    delete(appearance);
}
