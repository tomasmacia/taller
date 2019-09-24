#ifndef GAME_H_
#define GAME_H_

#include "background.h"
#include "object.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "GameObject.h"
#include "LogLib/LogManager.h"
#include "parser/config/config.h"
#include "game_component.h"

class Game
{
public:
    static Game& getInstance() {
        static Game instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    // gameloop
    void start();

    class Character* character;
    Background* back, *middle;
    Background* floor, *front;
    void move_all();
    void pj_in_final();
    bool isRunning = true; // false
    void level2(int enemy, int cajas,int barril, int tubos,int knifes,int width,int heigth);

    void addGameObject(GameObject *gameObject) {
        gameObjects.push_back(gameObject);
    }

    // wrapper getters
    Config* getConfig() {
        return config;
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

    // free memory
    void destroy();


    void reboot();

    std::vector<GameObject*> gameObjects;

    void UpdateAtras(vector<Game_Component*> vector);
    void UpdateDelante(vector<Game_Component*> vector);
    void setWindowTitleWithFPS(int fps);

    std::vector <string> g1;
    std::vector <string> gmiddle;
    std::vector <string> g2;
    std::vector <string> gfront;
    Game_Component* _enemy;
    std::vector <Game_Component*> obj_escenario;

    void level1(int enemy, int cajas,int barril, int tubos,int knifes,int width,int heigth);

    // wrappers
    Logger *logger; // since its a pointer allocating memory, we need to delete it later
    Config *config;
    SDL_Window *window;
    SDL_Renderer *renderer;

};

#endif