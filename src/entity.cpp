#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "appearance.h"

//CONSTRUCTOR & DESTRUCTOR
Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                 int r, int g, int b, int a){

    initAppearance(renderer,width,height,x,y,r,g,b,a);
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                 std::vector <Sprite*>* sprites){

    _spriteParser = new SpriteParser(sprites);
    initAppearance(renderer,width,height,x,y,_spriteParser->next());
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                 Sprite* sprite){    
    initAppearance(renderer,width,height,x,y,sprite);
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y){

    initAppearance(renderer,width,height,x,y,255,0,255,255);
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                    int r, int g, int b, int a, float minScaleFactor, float maxY, float minY,
                    bool perspectiveSensitive){

    _perspectiveSensitive = perspectiveSensitive;
    if (_perspectiveSensitive){
        initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
        width = applyPerspectiveTransformationTo(width,y);
        height = applyPerspectiveTransformationTo(height,y);
    }

    initAppearance(renderer,width,height,x,y,r,g,b,a);
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                 std::vector <Sprite*>* sprites, float minScaleFactor, float maxY, float minY,
                 bool perspectiveSensitive){

    _perspectiveSensitive = perspectiveSensitive;
    if (_perspectiveSensitive){
        initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
        width = applyPerspectiveTransformationTo(width,y);
        height = applyPerspectiveTransformationTo(height,y);
    }

    _spriteParser = new SpriteParser(sprites);
    initAppearance(renderer,width,height,x,y,_spriteParser->next());
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                 Sprite* sprite, float minScaleFactor, float maxY, float minY, 
                 bool perspectiveSensitive){    

    _perspectiveSensitive = perspectiveSensitive;
    if (_perspectiveSensitive){
        initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
        width = applyPerspectiveTransformationTo(width,y);
        height = applyPerspectiveTransformationTo(height,y);
    }    

    initAppearance(renderer,width,height,x,y,sprite);
    initPosition(x,y);
}

Entity::Entity(SDL_Renderer* renderer, float width, float height, float x, float y,
                float minScaleFactor, float maxY, float minY,
                bool perspectiveSensitive){

    _perspectiveSensitive = perspectiveSensitive;
    if (_perspectiveSensitive){
        initPerspectiveParameters(width,height,minScaleFactor,maxY,minY);
        width = applyPerspectiveTransformationTo(width,y);
        height = applyPerspectiveTransformationTo(height,y);
    }

    initAppearance(renderer,width,height,x,y,255,0,255,255);
    initPosition(x,y);
}

Entity::~Entity(){
    delete(_spriteParser);
    delete(_position);
    delete(_appearance);
}

//PUBLIC
void Entity::move(){
    changeXBy(_velocity_x);
    changeYBy(_velocity_y);
}

void Entity::enableLeftXMotion(){
    _velocity_x = -X_SPEED_CONSTANT;
}

void Entity::enableRightXMotion(){
    _velocity_x = X_SPEED_CONSTANT;
}

void Entity::enableUpYMotion(){
    _velocity_y = -Y_SPEED_CONSTANT;
}

void Entity::enableDownYMotion(){
    _velocity_y = Y_SPEED_CONSTANT;
}

void Entity::disableXMotion(){
    _velocity_x = 0;
}

void Entity::disableYMotion(){
    _velocity_y = 0;
}

void Entity::applyHorizontalLeftShift(){
    changeXBy(-X_SPEED_CONSTANT);
}

void Entity::applyHorizontalRighShift(){
    changeXBy(X_SPEED_CONSTANT);
}

void Entity::setSpeed(float speed){
    X_SPEED_CONSTANT = speed;
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

void Entity::changeXBy(float amount){
    _position->changeXBy(amount);
}

void Entity::changeYBy(float amount){
    _position->changeYBy(amount);

    if (_perspectiveSensitive && amount != 0){
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

float Entity::applyPerspectiveTransformationTo(float length, float y){
    float newLegth;
    float c = (1 - _minScaleFactor)/(_maxY - _minY);
    float scaleFactor = c*y + (1 - c*_maxY);
    newLegth = length * scaleFactor;
    return newLegth;
}

float Entity::correctXToSDLCoordinateSystem(float width, float height, float previousX){
    return previousX - width/2;
}

float Entity::correctYToSDLCoordinateSystem(float width, float height, float previousY){
    return previousY - height;
}

void Entity::initAppearance(SDL_Renderer* renderer, float width, float height,
                             float x, float y,  int r, int g, int b, int a){
    float correctedX = correctXToSDLCoordinateSystem(width,height,x);
    float correctedY = correctYToSDLCoordinateSystem(width,height,y);
    _appearance = new Appearance(renderer,width,height,correctedX,correctedY, r, g, b, a);
}

void Entity::initAppearance(SDL_Renderer* renderer, float width, float height,
                             float x, float y, Sprite* sprite){
    float correctedX = correctXToSDLCoordinateSystem(width,height,x);
    float correctedY = correctYToSDLCoordinateSystem(width,height,y);
    _appearance = new Appearance(renderer,width,height,correctedX,correctedY,sprite);
}

void Entity::initPosition(float x, float y){
    _position = new Position(x,y,_appearance);
}