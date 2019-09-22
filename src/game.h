#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "background.h"
#include "object.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "enemy.h"
#include "LogLib/LogManager.h"
#include "parser/config/config.h"

class Game
{
public:
    static Game* getInstance();

    // gameloop
    void start();

    class Character* character;
    Background* back, *middle;
    Background* floor, *front;
    void move_all();
    void pj_in_final();

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

private:
    static Game* instance;
    Game() {
        init();
    }

    ~Game() {
        destroy();
    }

    // inits
    void init();
    void initConfig();
    void initLogManager();
    void initSDL();

    // free memory
    void destroy();


    void reboot();

    void UpdateAtras(vector<Enemy*> vector);
    void UpdateDelante(vector<Enemy*> vector);
    Enemy* _enemy;
    class Window* _gwindow;
    void fpsChanged(int fps);
    bool isRunning = false;
    std::vector <string> g1;
    std::vector <string> gmiddle;
    std::vector <string> g2;
     std::vector <string> gfront;
    std::vector <Object*> barriles;
    std::vector <Enemy*> enemigos;
    void level1(int enemy, int objetos, int armas,int heigth,int width);

    // wrappers
    LogManager *logManager;
    Config *config;
    SDL_Window *window;
    SDL_Renderer *renderer;

};

#endif