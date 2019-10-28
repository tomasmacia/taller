#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include "Controller.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"
#include "Manager.h"
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


    // *************************
    // ******* METHODS *********
    // *************************

    void start();
    void end();
    void endLevel();
    int getCurrentLevelWidth();

    // *************************
    // ******* WRAPPERS ********
    // *************************

    Config* getConfig() {
        return config;
    }

    Controller* getController() {
        return controller;
    }

    Manager* getManager() {
        return manager;
    }

    SDL_Window* getWindow() {
        return window;
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

private:
    GameServer() {
        init();
    }

    ~GameServer() {
        destroy();
    }

    // inits
    void init();
    void initConfig();
    void initSDL();
    void initController();
    void initECSManager();

    // free memory
    void destroy();

    // gameloop
    void processInput();
    void update();
    void sendUpdate();

    bool isRunning;

    LevelBuilder* levelBuilder = nullptr;
    Controller *controller = nullptr;
    Manager* manager = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Config *config = nullptr;
};

#endif //GAME_GAMESERVER_H_