//
// Created by Tomás Macía on 05/09/2019.
//

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>
#include "config/bindings.h"
#include "config/gameplay.h"
#include "config/screenresolution.h"

using namespace std;

class Config {
public:
    string loggerLevel;
    Bindings bindings;
    ScreenResolution screenResolution;
    Gameplay gameplay;
};

#endif //GAME_CONFIG_H
