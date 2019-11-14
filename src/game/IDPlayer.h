//
// Created by axel on 28/10/19.
//

#ifndef GAME_IDPLAYER_H
#define GAME_IDPLAYER_H

#include <vector>

class IDPlayer { //cada pc tiene asignado un player id y es unico

public:
    //SINGLETON
    //===============================
    static IDPlayer &getInstance() {
        static IDPlayer instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    IDPlayer(IDPlayer const &) = delete;
    void operator=(IDPlayer const &) = delete;

    //API
    //===============================
    void addNewIdPlayer(int id);
    int getNextId();
    void initIDCounter();
    void reemplaze(int oldID, int newID);

private:
    IDPlayer(){}

    //ATRIBUTES
    //===============================
    std::vector<int> ids;
    int currentIdCounter;
};

#endif //GAME_IDPLAYER_H
