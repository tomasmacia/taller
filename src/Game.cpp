#include "Game.h"
#include <iterator>
#include <SDL2/SDL.h> 
#include "window.h"
#include <iostream>
#include <unistd.h>

bool end = false;

void Game::setup(){};

Game::Game(){
    std::vector<Displayable*> d;
    std::vector<Updateable*> u;
    this->displayables =  d;
    this->updateables =  u;
};

void Game::addDisplayable(Displayable* newdisp){
    this->displayables.push_back(newdisp);
};

void Game::addUpdateable(Updateable* newupd){
    this->updateables.push_back(newupd);
};

void Game::start(){

    while(!this->endCondition()){
        
        Game::readInput();
        for (int i = 0; i < this->updateables.size(); i++){
        this->updateables.at(i)->update();
        };
        for (int i = 0; i < this->displayables.size(); i++){
        this->displayables.at(i)->display();
        };
        usleep(16);
    }
};

void Game::readInput(){
    Controller::reset();
    SDL_Event e;
    while(SDL_PollEvent (&e ) != 0){
        if (e.type == SDL_QUIT){
            this->end = true;
        };
        if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_UP:
                    Controller::pressUp();
                    break;
                case SDLK_DOWN:
                    Controller::pressDown();
                    break;

                case SDLK_LEFT:
                    Controller::pressLeft();
                    break;

                case SDLK_RIGHT:
                    Controller::pressRight();
                    break;
            }
        }
    }
}


bool Game::endCondition(){
    return end;
}