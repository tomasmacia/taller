//
// Created by Tomás Macía on 08/12/2019.
//

#ifndef GAME_SOUNDS_H
#define GAME_SOUNDS_H

#include <string>
using namespace std;

class Boss {
public:
    string death;
};

class Music {
public:
    string soundtrack;
};

class NpcSound {
public:
    string death;
    string hit;
};

class PlayerSound {
public:
    string death;
    string great;
    string hit;
    string knifeHit;
    string pipeHit;
    string jump;
    string heehee;
};

class UtilitySound {
public:
    string barrelBreak;
    string boxBreak;
};

class Sounds {
public:
    Boss boss;
    Music music;
    NpcSound npcs;
    PlayerSound players;
    UtilitySound utilities;
};

#endif //GAME_SOUNDS_H
