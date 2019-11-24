//
// Created by axel on 28/10/19.
//

#include "IDManager.h"

//API
//=========================================================================================
void IDManager::addNewIdPlayer(int id){
    ids.push_back(id);
}

int IDManager::getNextId(){
    currentIdCounter ++;
    currentIdCounter = currentIdCounter % ids.size();
    return ids.at(currentIdCounter);
}

void IDManager::initIDCounter(){
    currentIdCounter = -1;
}

void IDManager::reemplaze(int oldID, int newID){
    for (int i = 0 ; i < ids.size(); i++){
        if (ids.at(i) == oldID){
            ids.at(i) = newID;
        }
    }
}