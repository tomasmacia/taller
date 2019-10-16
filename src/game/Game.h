#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "Controller.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"
#include "Manager.h"

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

    bool isRunning = true; // false
    bool levelFinished = false;

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
    void initLogManager(string loggerLevel);
    void initSDL();
    void initController();
    void initECSManager();

    // free memory
    void destroy();


    // gameloop
    void processInput();
    void update();
    void render();

    void setWindowTitleWithFPS(int fps);

    bool isGameRunning();

    bool hasNextLevel = false;

    // wrappers
    Logger *logger; // since its a pointer allocating memory, we need to delete it later
    Config *config;
    Controller *controller;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Manager* manager;

};

#endif