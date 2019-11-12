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
    currentIdCounter = currentIdCounter % ids.size();
    return ids.at(currentIdCounter);
}

void IDPlayer::initIDCounter(){
    currentIdCounter = -1;
}

void IDPlayer::reemplaze(int oldID, int newID){
    for (int i = 0 ; i < ids.size(); i++){
        if (ids.at(i) == oldID){
            ids.at(i) = newID;
        }
    }
}