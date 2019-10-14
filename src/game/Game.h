//
// Created by Tomás Macía on 09/10/2019.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "GameObject.h"
#include "Controller.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"

class Game {
public:
    static Game& getInstance() {
        static Game instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    bool static ifXOutOfRange(int x);
    bool static ifYOutOfRange(int y);

    // gameloop
    void start();


    bool isRunning = true; // false
    bool levelFinished = false;

    void addGameObject(GameObject *gameObject) {
        gameObjects.push_back(gameObject);
    }

    void destroyGameObjects();

    // wrapper getters
    Config* getConfig() {
        return config;
    }

    Controller* getController() {
        return controller;
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

    // free memory
    void destroy();

    // gameloop
    void processInput();
    void update();
    void render();

    bool isGameRunning();



    std::vector<GameObject*> gameObjects;


    void setWindowTitleWithFPS(int fps);


    bool hasNextLevel = false;


    // wrappers
    Logger *logger; // since its a pointer allocating memory, we need to delete it later
    Config *config;
    Controller *controller;
    SDL_Window *window;
    SDL_Renderer *renderer;


};


#endif //GAME_GAME_H
