#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "sprite_parser.h"
#include "square.h"

//CONSTRUCTOR & DESTRUCTOR
Entity::Entity(SDL_Renderer* renderer, float side, float x, float y, int r, int g, int b, int a){
    _square = new Square(renderer,side,x,y,r,g,b,a);
    _position = new Position(x,y,_square);
}

Entity::Entity(SDL_Renderer* renderer, float side, float x, float y, std::vector <std::string>& spritePaths){
    _spriteParser = new SpriteParser(spritePaths);
    _square = new Square(renderer,side,x,y,_spriteParser->next());
    _position = new Position(x,y,_square);
}

Entity::~Entity(){
    _square->~Square();
}

//PUBLIC
void Entity::handeEvent(SDL_Event e){
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: _velocity_y -= SPEED_CONSTANT; break;
            case SDLK_DOWN: _velocity_y += SPEED_CONSTANT; break;
            case SDLK_LEFT: _velocity_x -= SPEED_CONSTANT; break;
            case SDLK_RIGHT: _velocity_x += SPEED_CONSTANT; break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: _velocity_y += SPEED_CONSTANT; break;
            case SDLK_DOWN: _velocity_y -= SPEED_CONSTANT; break;
            case SDLK_LEFT: _velocity_x += SPEED_CONSTANT; break;
            case SDLK_RIGHT: _velocity_x -= SPEED_CONSTANT; break;
        }
    }
}

void Entity::move()
{
    _position->changeXBy(_velocity_x);
    _position->changeYBy(_velocity_y);
}

void Entity::update(){
    move();
}

void Entity::display(){
    _square->display();
}

//PRIVATE