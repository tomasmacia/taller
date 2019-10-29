//
// Created by axel on 28/10/19.
//

#ifndef GAME_IDPLAYER_H
#define GAME_IDPLAYER_H

#include <vector>

class IDPlayer { //cada pc tiene asignado un player id y es unico

public:
    static int addNewIdPlayer();
    static int getNextId();
    static void initIDCounter();
private:

    static std::vector<int> ids;
    static int currentIdCounter;
    static int lastIDGenerated;
};

#endif //GAME_IDPLAYER_H
