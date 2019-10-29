//
// Created by axel on 28/10/19.
//

#include "IDPlayer.h"

void IDPlayer::addNewPlayer(){
    this->lastIDGenerated ++;
}

int IDPlayer::getNewIdPlayer(){
    return this->lastIDGenerated;
}