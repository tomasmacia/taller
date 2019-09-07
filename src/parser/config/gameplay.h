//
// Created by Tomás Macía on 05/09/2019.
//

#ifndef GAME_GAMEPLAY_H
#define GAME_GAMEPLAY_H

#include <vector>
#include "level.h"
#include "character.h"
#include "npc.h"
#include "weapons.h"
#include "utilities.h"

using namespace std;

class Gameplay {
public:
    vector<Level> levels;
    vector<Character> characters;
    vector<NPC> npcs;
    Weapons weapons;
    Utilities utilities;
};

#endif //GAME_GAMEPLAY_H
