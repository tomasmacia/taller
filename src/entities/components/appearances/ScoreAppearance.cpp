//
// Created by axelmpm on 1/12/19.
//

#include "ScoreAppearance.h"

ScoreAppearance::ScoreAppearance(ScreenPosition *screenPosition, Score *score) : Appearance(screenPosition) {
    this->score = score;
}

void ScoreAppearance::update() {
    //TODO
}

Renderable *ScoreAppearance::actuallyGenerateRenderable() {
    return nullptr; //TODO
}

void ScoreAppearance::loadNextImage() {
    //TODO
}
