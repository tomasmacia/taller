//
// Created by axel on 28/11/19.
//

#include "Background.h"

Background::Background(Screen *screen, string spritePath, float parallaxSpeed, CollitionManager *collitionManager, list<CollitionBox*>* collitionBoxes) {

    this->collitionHandler = new BackgroundCollitionHandler(collitionManager, collitionBoxes);
    this->appearance = new BackgroundAppearance(screen, spritePath, parallaxSpeed);
}

void Background::update() {
    //no hace falta update a el collition handler por ahora
    appearance->update();
}

Sendable *Background::generateSendable() {
    auto renderable = appearance->generateRenderable();
    return new Sendable(renderable, nullptr);
}

Background::~Background() {
    delete(collitionHandler);
    delete(appearance);
}
