#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "appearance.h"

//CONSTRUCTOR & DESTRUCTOR
Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a){
    _appearance = new Appearance(renderer,width,height,x,y,r,g,b,a);
    _position = new Position(x,y,_appearance);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::vector <Sprite*>* sprites){
    _spriteParser = new SpriteParser(sprites);
    _appearance = new Appearance(renderer,width,height,x,y,_spriteParser->next());
    _position = new Position(x,y,_appearance);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite){    
    _appearance = new Appearance(renderer,width,height,x,y,sprite);
    _position = new Position(x,y,_appearance);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y){
    _appearance = new Appearance(renderer,width,height,x,y,255,255,255,255);
    _position = new Position(x,y,_appearance);
}

Entity::~Entity(){
    _appearance->~Appearance();
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

void Entity::applyHorizontalLeftShift(){
    _position->changeXBy(-SPEED_CONSTANT);
}

void Entity::applyHorizontalRighShift(){
    _position->changeXBy(SPEED_CONSTANT);
}

void Entity::setSpeed(float speed){
    SPEED_CONSTANT = speed;
}

void Entity::updateImage(){
    if (_spriteParser && animationRunning){
        _appearance->loadImage(_spriteParser->next());
    }
    _appearance->updateImage();
}

//PRIVATE