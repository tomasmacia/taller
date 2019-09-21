#include <iostream>
#include <SDL2/SDL_image.h>
#include "background.h"

//CONSTRUCTOR & DESTRUCTOR
Background::Background(SDL_Renderer* renderer,vector<Barrel*>* entitiesOnBackground,
                    float width, float height){

    _entitiesOnBackground = entitiesOnBackground;
    _renderer = renderer;

    float WHOLE_BACKBROUND_WIDTH = width;
    float WHOLE_BACKBROUND_HEIGHT = height;
    _entity = new Entity(renderer, WHOLE_BACKBROUND_WIDTH, WHOLE_BACKBROUND_HEIGHT, 
                                STARTING_WHOLE_BACKGROUND_X, STARTING_WHOLE_BACKGROUND_Y);

    createNearBackground();
    //createMiddleBackground();
    createFarBackground();
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

    for (int  i = 0; i < _entitiesOnBackground->size(); i++){
        _entitiesOnBackground->at(i)->applyHorizontalLeftShift();
    }
}

void Background::applyHorizontalRighShift(){                //PARALAX IMPLEMENTATION
    _entity->applyHorizontalRighShift();
    _nearBackground->applyHorizontalRighShift();
    //_middleBackground->applyHorizontalRighShift();
    _farBackground->applyHorizontalRighShift();

    for (int  i = 0; i < _entitiesOnBackground->size(); i++){
        _entitiesOnBackground->at(i)->applyHorizontalRighShift();
    }
}

void Background::setSpeed(float speed){
    WHOLE_BACKGROUND_SPEED = speed;
    FAR_BACKGROUND_SPEED = speed;
    //MIDDLE_BACKGROUND_SPEED = speed * 1.5;
    NEAR_BACKGROUND_SPEED = speed *2.5;
}

void Background::updateImage(){
    _nearBackground->updateImage();
    //_middleBackground->updateImage();
    _farBackground->updateImage();
}

//PRIVATE
void Background::createNearBackground(){
    std::vector <std::string> nearBackgroundSpritePaths;

    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor1.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor2.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor3.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor4.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor5.png");
    nearBackgroundSpritePaths.push_back("Sprites/FF_Stage4_floor6.png");

    _nearBackground = new Entity(_renderer, NEAR_BACKGROUND_WIDTH, NEAR_BACKGROUND_HEIGHT,
                                 STARTING_NEAR_BACKGROUND_X, STARTING_NEAR_BACKGROUND_Y,
                                 nearBackgroundSpritePaths);
    _nearBackground->setSpeed(NEAR_BACKGROUND_SPEED);                       
}

void Background::createFarBackground(){
    std::vector <std::string> farBackgroundSpritePaths;

    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back1.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back2.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back3.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back4.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back5.png");
    farBackgroundSpritePaths.push_back("Sprites/FF_Stage4_back6.png");

    _farBackground = new Entity(_renderer, FAR_BACKGROUND_WIDTH, FAR_BACKGROUND_HEIGHT,
                         STARTING_WHOLE_BACKGROUND_X, STARTING_WHOLE_BACKGROUND_Y,
                         farBackgroundSpritePaths);
    _farBackground->setSpeed(FAR_BACKGROUND_SPEED);
}