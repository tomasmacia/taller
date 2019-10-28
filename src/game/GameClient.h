#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

#include "Controller.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"

class GameClient {
public:
    // *************************
    // ******* SINGLETON *******
    // *************************

    static GameClient &getInstance() {
        static GameClient instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    GameClient(GameClient const &) = delete;
    void operator=(GameClient const &) = delete;


    // *************************
    // ******* METHODS *********
    // *************************

    void start();
    SDL_Renderer* getRenderer(){
        return renderer;
    }

    // *************************
    // ******* WRAPPERS ********
    // *************************

    Config* getConfig() {
        return config;
    }

    Controller* getController() {
        return controller;
    }

private:
    GameClient() {
        init();
    }

    ~GameClient() {
        destroy();
    }

    // inits
    void init();
    void initConfig();
    void initSDL();
    void initController();

    // free memory
    void destroy();

    // gameloop
    void sendInput();
    void render();

    bool isRunning;

    Controller *controller = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Config *config = nullptr;

};

#endif //GAME_GAMECLIENT_H_
