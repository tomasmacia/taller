#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "Controller.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"
#include "Manager.h"
#include "LevelBuilder.h"

class Game {
public:
    // *************************
    // ******* SINGLETON *******
    // *************************
    static Game& getInstance() {
        static Game instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    // *************************
    // ****** ENTRYPOINT *******
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
    Game() {
        init();
    }

    ~Game() {
        destroy();
    }

    // inits
    void init();
    void initConfig();
    void setLogManager();
    void initSDL();
    void initController();
    void initECSManager();

    // free memory
    void destroy();


    // gameloop
    void processInput();
    void update();
    void render();

    // wrappers
    LevelBuilder* levelBuilder = nullptr;
    Controller *controller = nullptr;
    Manager* manager = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Config *config = nullptr;

};

#endif