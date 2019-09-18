
#include "Updateable.h"
#include "Displayable.h"
#include "Controller.h"
#include <vector>
#include <config/config.h>
#include "../LogLib/LogManager.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
    Game() {
        init();
    }

    ~Game() {
        destroy();
    }

    bool gameFinished;
    std::vector<Updateable*> updateables;
    std::vector<Displayable*> displayables;

    // gameloop
    void readInput();
    void update();
    void display();

    // free memory
    void destroy();

    // inits
    void init();
    void initConfig();
    void initLogManager();
    void initSDL();

    // wrappers
    LogManager *logManager;
    Config *config;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    static Game &getInstance() {
        static Game instance; // Guaranteed to be destroyed.

        return instance;
    }

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    void start();
    void addUpdateable(Updateable* newUpdateable);
    void addDisplayable(Displayable* newDisplayable);
    bool isRunning();

    // wrapper getters
    LogManager& getLogManager();
    Config& getConfig();
};

#endif