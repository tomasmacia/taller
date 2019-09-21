#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "barrel.h"
using namespace std;

class Background {

private:

  Entity* _entity;              //es el background como un todo
  Entity* _nearBackground;
  //Entity* _middleBackground;          //IMPLEMENTAR
  Entity* _farBackground;

  float NEAR_BACKGROUND_WIDTH;
  float NEAR_BACKGROUND_HEIGHT;
  float STARTING_NEAR_BACKGROUND_X;
  float STARTING_NEAR_BACKGROUND_Y;
  float NEAR_BACKGROUND_SPEED;

  //float MIDDLE_BACKGROUND_WIDTH;      //IMPLEMENTAR       
  //float MIDDLE_BACKGROUND_HEIGHT;     //IMPLEMENTAR
  //float STARTING_MIDDLE_BACKGROUND_X;          //IMPLEMENTAR
  //float STARTING_MIDDLE_BACKGROUND_Y;          //IMPLEMENTAR
  //float MIDDLE_BACKGROUND_SPEED;          //IMPLEMENTAR

  float FAR_BACKGROUND_WIDTH;
  float FAR_BACKGROUND_HEIGHT;
  float STARTING_FAR_BACKGROUND_X;
  float STARTING_FAR_BACKGROUND_Y;
  float FAR_BACKGROUND_SPEED = NEAR_BACKGROUND_SPEED/3;

  float WHOLE_BACKBROUND_WIDTH;
  float WHOLE_BACKBROUND_HEIGHT;
  float STARTING_WHOLE_BACKGROUND_X = STARTING_FAR_BACKGROUND_X;
  float STARTING_WHOLE_BACKGROUND_Y = STARTING_FAR_BACKGROUND_Y;
  float WHOLE_BACKGROUND_SPEED = FAR_BACKGROUND_SPEED;

  vector<Barrel*>* _entitiesOnBackground;
  SDL_Renderer* _renderer;

public:
    
    Background(SDL_Renderer* renderer,vector<Barrel*>* entitiesOnBackground,
             float width, float height);
    ~Background();

    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    void updateImage();

private:

    void nextBackground(const std::string &image_path);

    void createNearBackground();
    //void createMiddleBackground();    //IMPLEMENTAR
    void createFarBackground();

};

#endif