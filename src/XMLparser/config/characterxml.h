//
// Created by Tomás Macía on 05/09/2019.
//

#ifndef GAME_CHARACTERXML_H
#define GAME_CHARACTERXML_H

#include <string>
#include "EntityConfig.h"

using namespace std;

class CharacterXML : public EntityConfig {
public:
    string name;
    string disconnected;

};

#endif //GAME_CHARACTERXML_H
