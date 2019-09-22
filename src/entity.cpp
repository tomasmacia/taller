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

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a, float minScaleFactor, float maxY, float minY){

    initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
    float newWidth = applyPerspectiveTransformationTo(width,y);
    float newHeight = applyPerspectiveTransformationTo(height,y);

    _appearance = new Appearance(renderer,newWidth,newWidth,x,y,r,g,b,a);
    _position = new Position(x,y,_appearance);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::vector <Sprite*>* sprites, float minScaleFactor, float maxY, float minY){

    initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
    float newWidth = applyPerspectiveTransformationTo(width,y);
    float newHeight = applyPerspectiveTransformationTo(height,y);

    _spriteParser = new SpriteParser(sprites);
    _appearance = new Appearance(renderer,newWidth,newHeight,x,y,_spriteParser->next());
    _position = new Position(x,y,_appearance);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite, float minScaleFactor, float maxY, float minY){    

    initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
    float newWidth = applyPerspectiveTransformationTo(width,y);
    float newHeight = applyPerspectiveTransformationTo(height,y);    

    _appearance = new Appearance(renderer,newWidth,newHeight,x,y,sprite);
    _position = new Position(x,y,_appearance);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y, float minScaleFactor, float maxY, float minY){

    initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
    float newWidth = applyPerspectiveTransformationTo(width,y);
    float newHeight = applyPerspectiveTransformationTo(height,y);

    _appearance = new Appearance(renderer,newWidth,newHeight,x,y,255,255,255,255);
    _position = new Position(x,y,_appearance);
}

Entity::~Entity(){
    delete(_spriteParser);
    delete(_position);
    delete(_appearance);
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

void Entity::move(){
    changeXBy(_velocity_x);
    changeYBy(_velocity_y);
}

void Entity::enableLeftXMotion(){
    _velocity_x = SPEED_CONSTANT;
}

void Entity::enableRightXMotion(){
    _velocity_x = -SPEED_CONSTANT;
}

void Entity::enableUpYMotion(){
    _velocity_y = SPEED_CONSTANT;
}

void Entity::enableDownYMotion(){
    _velocity_y = -SPEED_CONSTANT;
}

void Entity::disableXMotion(){
    _velocity_x = 0;
}

void Entity::disableYMotion(){
    _velocity_y = 0;
}

void Entity::applyHorizontalLeftShift(){
    changeXBy(-SPEED_CONSTANT);
}

void Entity::applyHorizontalRighShift(){
    changeXBy(SPEED_CONSTANT);
}

void Entity::setSpeed(float speed){
    SPEED_CONSTANT = speed;
}

float Entity::getY(){
    return _position->getY();
}

float Entity::getWidth(){
    return _appearance->getWidth();
}

float Entity::getHeigth(){
    return _appearance->getHeigth();
}

void Entity::update(){
    move();
    updateImage();
}

void Entity::updateImage(){
    if (_spriteParser && animationRunning){
        _appearance->loadImage(_spriteParser->next());
    }
    _appearance->updateImage();
}

//PRIVATE
void Entity::initPerspectiveParameters(float width, float height, float minScaleFactor, float maxY, float minY){
    
    _perspectiveSensible = true;
    _minScaleFactor = minScaleFactor;
    _maxWidth = width;
    _maxHeight = height;
    _maxY = maxY;
    _minY = minY;

    /*
    std::cout <<"_perspectiveSensible: "<< _perspectiveSensible << "\n";
    std::cout <<"_minScaleFactor: "<< _minScaleFactor << "\n";
    std::cout <<"_maxWidth: "<< _maxWidth << "\n";
    std::cout <<"_maxHeight: "<< _maxHeight << "\n";
    std::cout <<"_maxY: "<< _maxY << "\n";
    std::cout <<"_minY: "<< _minY << "\n";
    */
}

float Entity::applyPerspectiveTransformationTo(float length, float y){
    float newLegth;
    float c = (1 - _minScaleFactor)/(_maxY - _minY);
    float scaleFactor = c*y + (1 - c*_maxY);
    newLegth = length * scaleFactor;
    return newLegth;
}

void Entity::changeXBy(float amount){
    _position->changeXBy(amount);
}

void Entity::changeYBy(float amount){
    _position->changeYBy(amount);

    if (_perspectiveSensible && amount != 0){
        applyPersepective();
    }
}

void Entity::applyPersepective(){

    float y = _position->getY();
    float width = _appearance->getWidth();
    float height = _appearance->getHeigth();

    float newWidth = applyPerspectiveTransformationTo(width,y);
    float newHeight = applyPerspectiveTransformationTo(height,y);

    _appearance->setWidth(newWidth);
    _appearance->setHeight(newHeight);
}