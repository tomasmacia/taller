#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"
class Controller;

class Game {
public:

    virtual void start() = 0;

    // *************************
    // ******* METHODS *********
    // *************************

    void end();
    virtual std::string pollMessage(){}

    // *************************
    // ******* WRAPPERS ********
    // *************************

    Config* getConfig() {
        return config;
    }

    Controller* getController() {
        return controller;
    }

    SDL_Renderer* getRenderer(){
        return renderer;
    }

    int getPlayerId(){
        return playerId;
    }

protected:

    virtual void init() = 0;
    virtual void destroy() = 0;
    void baseClassFreeMemory();

    virtual void initController();
    void initConfig();
    void initSDL();

    bool isRunning;
    int playerId = -1;

    Controller *controller = nullptr;
    Config *config = nullptr;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif