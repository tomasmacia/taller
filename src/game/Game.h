#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "SceneDirector.h"
#include "../logger/LogManager.h"
#include "../XMLparser/config/config.h"

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
    void pauseResumeMusic();
    void pauseMusic();

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
    void initSceneDirector();

    //ATRIBUTES
    //===============================

    bool on = true;
    int playerId = -1;

    bool youDiedMusicPlaying = false;
    bool normalGameMusicPlaying = false;
    bool gameWonMusicPlaying = false;
    bool gameLostMusicPlaying = false;

    SceneDirector* sceneDirector = nullptr;
    Controller *controller = nullptr;
    Config *config = nullptr;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif