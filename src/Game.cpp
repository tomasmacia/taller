#include "Game.h"
#include <iterator>
#include <SDL2/SDL.h> 

bool end = false;

void Game::setup(){};

void Game::addDisplayable(Displayable newdisp){
    this->Game::displayables.push_front(newdisp);
};

void Game::addUpdateable(Updateable newupd){
    this->Game::updateables.push_front(newupd);
};

void Game::start(){
    while(!this->endCondition()){
        Game::readInput();
        for (auto & i : Game::updateables) {
        i.update();
        };
        for (auto & i : Game::displayables) {
        i.display();
        };
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