//
// Created by Tomás Macía on 06/09/2019.
//

#ifndef GAME_NPC_H
#define GAME_NPC_H

#include <string>
#include "EntityConfig.h"

using namespace std;

class NPC : public EntityConfig{
public:
    string difficulty; // maybe map it as an enum?
};

#endif //GAME_NPC_H
