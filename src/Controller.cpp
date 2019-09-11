#include "Controller.h"


bool Controller::up = false;
bool Controller::down = false;
bool Controller::left = false;
bool Controller::right = false;

void Controller::reset(){
    Controller::up,Controller::down,Controller::left,Controller::right = false;
};

void Controller::pressUp(){
    up = true;
};

void Controller::pressDown(){
    Controller::down = true;
};

void Controller::pressLeft(){
    Controller::left = true;
};

void Controller::pressRight(){
    Controller::right = true;
};

bool Controller::upIsPressed(){
    return Controller::up;
};
bool Controller::leftIsPressed(){
    return Controller::left;
};
bool Controller::rightIsPressed(){
    return Controller::right;
};
bool Controller::downIsPressed(){
    return Controller::down;
};