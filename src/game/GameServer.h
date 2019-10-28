#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include "LevelBuilder.h"

class GameServer {
public:

    // *************************
    // ******* SINGLETON *******
    // *************************

    static GameServer &getInstance() {
        static GameServer instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    GameServer(GameServer const &) = delete;
    void operator=(GameServer const &) = delete;


    void start();

private:
    GameServer() {}

    bool isRunning;

    LevelBuilder* levelBuilder = nullptr;
};

#endif //GAME_GAMESERVER_H_