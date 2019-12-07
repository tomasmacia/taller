//
// Created by axelmpm on 30/11/19.
//

#include "ScreenPosition.h"

ScreenPosition::ScreenPosition(int width, int height, Position *position, Screen* screen) {

    this->_spacePosition = position;
    this->_screen = screen;
    this->width = width;
    this->height = height;
    update();
}

void ScreenPosition::update(){
    x = _spacePosition->getX() - _screen->currentX;
    y = _screen->getWindowHeight() - (_spacePosition->getY() + _spacePosition->getZ()) - height;
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

int ScreenPosition::getWidth() {
    return width;
}

int ScreenPosition::getHeight() {
    return height;
}