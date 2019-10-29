//
// Created by axel on 28/10/19.
//

#include "IDPlayer.h"

int lastIDGenerated = 0; //el cero esta reservado para el NULL
int currentIdCounter = 0;
std::vector<int> ids;

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