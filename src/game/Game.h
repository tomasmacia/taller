#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"

class Controller;

class Game {
public:

    //ENTRY POINT
    //===============================
    virtual void start() = 0;

    //API
    //===============================
    virtual void end();
    bool isOn();

    //GETTERS
    //===============================
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

    void pauseResumeMusic();
    void sound();
protected:

    //GAME LOOP
    //===============================
    virtual void gameLoop() = 0;

    //DESTROY
    //===============================
    virtual void destroy() = 0;
    void baseClassFreeMemory();

    //INIT
    //===============================
    virtual void init() = 0;
    virtual void initController();
    void initConfig();
    void initSDL();

    //ATRIBUTES
    //===============================
    bool on = true;
    int playerId = -1;

    Controller *controller = nullptr;
    Config *config = nullptr;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    //SOUND
    //===============================
    Mix_Music* music;
    Mix_Chunk* sound1;
    void init_music();
    void close_music();
    

};

#endif