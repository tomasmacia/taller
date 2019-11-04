//
// Created by axel on 28/10/19.
//

#include "IDPlayer.h"

//API
//=========================================================================================
void IDPlayer::addNewIdPlayer(int id){
    ids.push_back(id);
}

int IDPlayer::getNextId(){
    currentIdCounter ++;
    return ids.at(currentIdCounter) % ids.size();
}
void IDPlayer::initIDCounter(){
    currentIdCounter = -1;
}