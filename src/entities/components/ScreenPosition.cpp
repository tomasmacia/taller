//
// Created by axelmpm on 30/11/19.
//

#include "ScreenPosition.h"

ScreenPosition::ScreenPosition(Position *position, Screen* screen) {

    this->_spacePosition = position;
    this->_screen = screen;
    update();
}

void ScreenPosition::update(){
    x = _spacePosition->getX() - _screen->currentX;
    y = _screen->getWindowHeight() - (_spacePosition->getY() + _spacePosition->getZ());
}

int ScreenPosition::getX() {
    return x;
}

int ScreenPosition::getY() {
    return y;
}

bool ScreenPosition::onScreen() {
    return _screen->onScreen(getX(),getY());
}
