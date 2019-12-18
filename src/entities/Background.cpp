//
// Created by axel on 28/11/19.
//

#include "Background.h"

Background::Background(BackgroundCollitionHandler *pHandler, BackgroundAppearance *pAppearance) : Entity(pHandler){
    this->appearance = pAppearance;
}

Background::Background(BackgroundAppearance* appearance) {
    this->appearance = appearance;
}

void Background::update() {
    appearance->update();
}

list<Sendable*> Background::generateSendable() {
    list<Sendable*> sendables;
    auto renderable = appearance->generateRenderable();
    sendables.push_back(new Sendable(renderable, nullptr));

    return sendables;
}

Background::~Background() {
    delete(appearance);
}
