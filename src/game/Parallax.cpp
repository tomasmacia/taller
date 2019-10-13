//
// Created by Tomás Macía on 09/10/2019.
//

#include "Parallax.h"

Parallax::Parallax() {

}

void Parallax::update() {
    for (auto &background : backgrounds) {
        background->update();
    }
}

void Parallax::render() {
    for (auto &background : backgrounds) {
        background->render();
    }
}

void Parallax::addNewBackground(Background *background) {
    backgrounds.push_back(background);
}


void Parallax::destroy() {
    for (auto &background : backgrounds) {
        delete(background);
        background = nullptr;
    }
}
