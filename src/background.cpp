#include <iostream>
#include <SDL2/SDL_image.h>
#include "background.h"

//CONSTRUCTOR & DESTRUCTOR
Background::Background(SDL_Renderer* renderer, float width, float height){

    _renderer = renderer;
    createNearBackground(width, height);
    //createMiddleBackground();
    createFarBackground();
    createBackgroundEntity();

    setSpeed(SPEED_PARAMETER);
}

Background::~Background(){              //DOES NOT HANDLES THE ENTITIES ON HIM
    delete(_entity);
    delete(_nearBackground);
    //delete(_middleBackground);
    delete(_farBackground);
}

//PUBLIC
void Background::applyHorizontalLeftShift(){                //PARALAX IMPLEMENTATION
    _entity->applyHorizontalLeftShift();
    _nearBackground->applyHorizontalLeftShift();
    //_middleBackground->applyHorizontalLeftShift();
    _farBackground->applyHorizontalLeftShift();

    if (_entitiesOnBackground){
        for (int  i = 0; i < _entitiesOnBackground->size(); i++){
            _entitiesOnBackground->at(i)->applyHorizontalLeftShift();
        }
    }
}

void Background::applyHorizontalRighShift(){                //PARALAX IMPLEMENTATION
    _entity->applyHorizontalRighShift();
    _nearBackground->applyHorizontalRighShift();
    //_middleBackground->applyHorizontalRighShift();
    _farBackground->applyHorizontalRighShift();

    if (_entitiesOnBackground){
        for (int  i = 0; i < _entitiesOnBackground->size(); i++){
            _entitiesOnBackground->at(i)->applyHorizontalRighShift();
        }
    }
}

void Background::setSpeed(float speed){                     //PARALAX IMPLEMENTATION
    _nearBackgroundSpeed = speed;
    //_middleBackgroundSpeed = speed * SPEED_FACTOR_MIDDLE_TO_NEAR;
    _farBackgroundSpeed = speed * SPEED_FACTOR_NEAR_TO_FAR;
    _wholeBackgroundSpeed = speed * SPEED_FACTOR_NEAR_TO_FAR;

    _nearBackground->setSpeed(_nearBackgroundSpeed); 
    //_middleBackground->setSpeed(_middleBackgroundSpeed); 
    _farBackground->setSpeed(_farBackgroundSpeed);           //ACORDARSE DE DESCOMENTAR
    _entity->setSpeed(_wholeBackgroundSpeed);

    if (_entitiesOnBackground){
        for (int  i = 0; i < _entitiesOnBackground->size(); i++){
            _entitiesOnBackground->at(i)->setSpeed(_nearBackgroundSpeed);
        }
    }
}

void Background::setGameObjects(vector<Barrel*>* entitiesOnBackground){
    _entitiesOnBackground = entitiesOnBackground;
    setSpeed(SPEED_PARAMETER);
}

float Background::getWidth(){
    return _wholeBackgroundWidth;
}

void Background::updateImage(){
    _farBackground->updateImage();
    //_middleBackground->updateImage();
    _nearBackground->updateImage();
}

//PRIVATE
void Background::createNearBackground(float width, float height){

    _nearBackgroundWidth = width * WIDTH_SCALE_FACTOR_SCREEN_TO_NEAR;
    _nearBackgroundHeight = height * HEIGHT_SCALE_FACTOR_SCREEN_TO_NEAR;
    _startingNearBackgroundX = 0;
    _startingNearBackgroundY = 0;

    /*
    std::vector <std::string> nearBackgroundSpritePaths;

    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor1.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor2.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor3.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor4.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor5.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor6.png");
    */
    Sprite* nearBackgroundSprite = new Sprite("Sprites/FF_Stage4_floor.png",
                                                        0,162,232);

    _nearBackground = new Entity(_renderer, _nearBackgroundWidth, _nearBackgroundHeight,
                                 _startingNearBackgroundX, _startingNearBackgroundY,
                                 nearBackgroundSprite);                      
}

void Background::createFarBackground(){

    _farBackgroundWidth = _wholeBackgroundWidth * WIDTH_SCALE_FACTOR_SCREEN_TO_FAR;
    _farBackgroundHeight = _wholeBackgroundHeight * HEIGHT_SCALE_FACTOR_SCREEN_TO_FAR;
    _startingFarBackgroundX = _startingWholeBackgroundX;
    _startingFarBackgroundY = _startingWholeBackgroundY;
    /*
    std::vector <std::string> farBackgroundSpritePaths;

    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back1.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back2.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back3.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back4.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back5.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back6.png");
    */
    Sprite* farBackgroundSprite = new Sprite("Sprites/FF_Stage4_back.png",
                                                        255,255,255);
    _farBackground = new Entity(_renderer, _farBackgroundWidth, _farBackgroundHeight,
                         _startingFarBackgroundX, _startingFarBackgroundY,
                         farBackgroundSprite);
}

void Background::createBackgroundEntity(){
    _wholeBackgroundWidth = _nearBackgroundWidth;
    _wholeBackgroundHeight = _farBackgroundHeight;
    _startingWholeBackgroundX = _startingFarBackgroundX;
    _startingWholeBackgroundY = _startingFarBackgroundY;
    _entity = new Entity(_renderer, _wholeBackgroundWidth, _wholeBackgroundHeight, 
                                _startingWholeBackgroundX, _startingWholeBackgroundY);
}