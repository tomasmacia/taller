#ifndef GAME_H_
#define GAME_H_

#include <cstdlib>
#include <vector>
#include <iostream>
#include "window.h"
#include "background.h"
#include "barrel.h"
#include "character.h"
#include "event_handler.h"

class Game
{
private:
    bool isRunning = true;

    float _width;
    float _height;
    const std::string GAME_NAME = "Final Figth";

    //VALID RANGE OF MOVEMENT
    float _maxY;
    float _minY;
    float WALKABLE_BACKGROUND_PERCENTAGE = 0.6;
    float OFFSET = 100;

    //GAME OBJECTS AMOUNTS
    int BARREL_AMOUNT = 20;
    int BOX_AMOUNT;
    int METALIC_TUBE_AMOUNT;
    int KNIFE_AMOUNT;

    //PERSEPCTIVE
    float MIN_SCALE_FACTOR = 0.35;   

    Character* character = nullptr;
    Background* _background  = nullptr;
    std::vector <Barrel*> _entities; //ONLY GAME OBJECTS
    
    EventHandler* _eventHandler = nullptr;
    Window* _window = nullptr;
    SDL_Renderer* _renderer;

public:
/*Constructor*/
    Game(int width, int heigth);
 /*Destructor*/
    ~Game();

    void handleInput();
    void update();
    void displaya();

    bool isClosed();
    void move_all();

private:   
    void intializeGameObjects();
    void fpsChanged(int fps);
};
#endif