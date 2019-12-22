//
// Created by Tomás Macía on 05/09/2019.
//

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>
#include "bindings.h"
#include "gameplay.h"
#include "Sounds.h"
#include "screenresolution.h"

using namespace std;

class Config {
public:
    string loggerLevel;
    int serverMaxPlayers;
    Bindings bindings;
    Sounds sounds;
    ScreenResolution screenResolution;
    Gameplay gameplay;
};

#endif //GAME_CONFIG_H
