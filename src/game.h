#ifndef GAME_H_
#define GAME_H_

#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "window.h"
#include "background.h"

class Game
{
private:
    bool isRunning = true;

    int _width;
    int _height;

    class Character* character;
    Background* _background;
    vector<Entity>* _entities;  //NOT THE BACKGROUND NOR THE MAIN CHARACTER

    std::vector <string> g1;
    std::vector <string> g2;
    std::vector <Object*> barriles;

    Window* _gwindow;
    SDL_Renderer* _renderer;

public:
/*Constructor*/
    Game(int width, int heigth);                //refactorizado
 /*Destructor*/
    ~Game();

    void runLoop();
    void move_all();
    void pj_in_final();

    bool isClosed();                            //agregado

private:
    void initialize();                          //refactorizado
    void allCreator(int width, int heigth);     //revisado (esta bastante bien)    
    vector<Entity>* intializeEntities();        //refactorizado
    void fpsChanged(int fps);                   //revisado (esta bastante bien)
};
#endif