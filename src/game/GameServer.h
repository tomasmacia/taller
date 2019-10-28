#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include "Manager.h"
#include "LevelBuilder.h"
#include "Game.h"

class GameServer : public  Game{
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


    // *************************
    // ******* METHODS *********
    // *************************

    void start() override ;
    void endLevel();
    int getCurrentLevelWidth();

    // *************************
    // ******* WRAPPERS ********
    // *************************

    Manager* getManager() {
        return manager;
    }

protected:
    void init() override ;
    void destroy() override ;

private:
    GameServer() {
        init();
    }
    ~GameServer() {
        destroy();
    }

    // inits
    void initECSManager();

    // gameloop
    void processInput();
    void update();
    void sendUpdate();

    LevelBuilder* levelBuilder = nullptr;
    Manager* manager = nullptr;
};

#endif //GAME_GAMESERVER_H_