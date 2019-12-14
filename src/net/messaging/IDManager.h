//
// Created by axel on 28/10/19.
//

#ifndef GAME_IDMANAGER_H
#define GAME_IDMANAGER_H

#include <vector>

class IDManager { //cada pc tiene asignado un player type y es unico

public:
    //SINGLETON
    //===============================
    static IDManager &getInstance() {
        static IDManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    IDManager(IDManager const &) = delete;
    void operator=(IDManager const &) = delete;

    //API
    //===============================
    void addNewIdPlayer(int id);
    int getNextId();
    void initIDCounter();
    void reemplaze(int oldID, int newID);
    int amount();

private:
    IDManager(){}

    //ATRIBUTES
    //===============================
    std::vector<int> ids;
    int currentIdCounter;
};

#endif //GAME_IDMANAGER_H
