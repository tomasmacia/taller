//
// Created by axel on 28/10/19.
//

#include "IDPlayer.h"

int lastIDGenerated = 0; //el cero esta reservado para el NULL
int currentIdCounter = 0;
std::list<int> ids;

void IDPlayer::addNewIdPlayer(){
    lastIDGenerated ++;
    ids.push_back(lastIDGenerated);
}

int IDPlayer::getNextId(){
    currentIdCounter ++;
    return ids. % ids.size();
}
void IDPlayer::initIDCounter(){
    currentIdCounter = 1;
}