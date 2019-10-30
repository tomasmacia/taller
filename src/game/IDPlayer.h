//
// Created by axel on 28/10/19.
//

#ifndef GAME_IDPLAYER_H
#define GAME_IDPLAYER_H

#include <vector>

class IDPlayer { //cada pc tiene asignado un player id y es unico

public:
    static IDPlayer &getInstance() {
        static IDPlayer instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    IDPlayer(IDPlayer const &) = delete;
    void operator=(IDPlayer const &) = delete;

    int addNewIdPlayer();
    int getNextId();
    void initIDCounter();

private:
    IDPlayer(){}

    std::vector<int> ids;
    int currentIdCounter = 0;
    int lastIDGenerated = 0; //el cero esta reservado para el NULL
};

#endif //GAME_IDPLAYER_H
