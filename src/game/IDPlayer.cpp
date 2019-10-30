//
// Created by axel on 28/10/19.
//

#include "IDPlayer.h"

int IDPlayer::addNewIdPlayer(){
    lastIDGenerated ++;
    ids.push_back(lastIDGenerated);
    return lastIDGenerated;
}

int IDPlayer::getNextId(){
    currentIdCounter ++;
    return ids.at(currentIdCounter) % ids.size();
}
void IDPlayer::initIDCounter(){
    currentIdCounter = 1;
}