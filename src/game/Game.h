
#include "Updateable.h"
#include "Displayable.h"
#include "Controller.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <config/config.h>
#include "../LogLib/LogManager.h"
#include "GameObject.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
    static Game* instance;
    Game() {
        init();
    }

    ~Game() {
        destroy();
    }

    bool gameFinished;
    bool hasNextLevel;
    std::vector<GameObject*> gameObjects;
    //std::vector<Updateable*> updateables;
    //std::vector<Displayable*> displayables;

    // gameloop
    void readInput();
    void update();
    void render();

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
    static Game* getInstance();

    void start();
    bool isRunning();

    void addGameObject(GameObject* gameObject);
    GameObject *player = nullptr;

    // wrapper getters
    LogManager* getLogManager() {
        return logManager;
    }

    Config* getConfig() {
        return config;
    }

    SDL_Window* getWindow() {
        return window;
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

};

#endif