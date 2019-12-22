//
// Created by Tomás Macía on 05/09/2019.
//

#ifndef GAME_GAMEPLAY_H
#define GAME_GAMEPLAY_H

#include <vector>
#include "level.h"
#include "characterxml.h"
#include "npc.h"
#include "weapons.h"
#include "utilities.h"

using namespace std;

class Gameplay {
public:
    vector<Level> levels;
    vector<CharacterXML> characters;
    NPC boss;
    vector<NPC> npcs;
    Weapons weapons;
    Utilities utilities;
};

#endif //GAME_GAMEPLAY_H
