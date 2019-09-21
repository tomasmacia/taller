#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "barrel.h"
using namespace std;

class Background {

private:

  Entity* _entity = nullptr;              //es el background como un todo INTUYO QUE VA A SER UTIL DESPUES AUNQUE AHORA NO LO USE TANTO
  Entity* _nearBackground = nullptr;
  //Entity* _middleBackground = nullptr;         //IMPLEMENTAR
  Entity* _farBackground = nullptr;

  float SPEED_PARAMETER = 10;                     //PARALLAX
  float SPEED_FACTOR_NEAR_TO_MIDDLE = 0.3;        //PARALLAX
  float SPEED_FACTOR_NEAR_TO_FAR = 0.07;          //PARALLAX

  float WIDTH_SCALE_FACTOR_SCREEN_TO_NEAR = 23;
  float HEIGHT_SCALE_FACTOR_SCREEN_TO_NEAR = 1;

  float WIDTH_SCALE_FACTOR_SCREEN_TO_FAR = 4;
  float HEIGHT_SCALE_FACTOR_SCREEN_TO_FAR = 0.8;

  float _nearBackgroundWidth;
  float _nearBackgroundHeight;
  float _startingNearBackgroundX;
  float _startingNearBackgroundY;
  float _nearBackgroundSpeed;

  //float _middleBackgroundWidth;               //IMPLEMENTAR       
  //float _middleBackgroundHeight;              //IMPLEMENTAR
  //float _startingMiddleBackgroundX;           //IMPLEMENTAR
  //float _startingMiddleBackgroundY;           //IMPLEMENTAR
  //float _middleBackgroundSpeed;               //IMPLEMENTAR

  float _farBackgroundWidth;
  float _farBackgroundHeight;
  float _startingFarBackgroundX;
  float _startingFarBackgroundY;
  float _farBackgroundSpeed;

  float _wholeBackgroundWidth;
  float _wholeBackgroundHeight;
  float _startingWholeBackgroundX;
  float _startingWholeBackgroundY;
  float _wholeBackgroundSpeed;

  vector<Barrel*>* _entitiesOnBackground = nullptr;
  SDL_Renderer* _renderer = nullptr;

public:
    
    Background(SDL_Renderer* renderer, float width, float height);
    ~Background();

    float getWidthScaleFactorScreenToNear();
    void setGameObjects(vector<Barrel*>* entitiesOnBackground);

    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    void updateImage();

private:

    void nextBackground(const std::string &image_path);

    void createBackgroundEntity(float width, float height);
    void createNearBackground();
    //void createMiddleBackground();            //IMPLEMENTAR
    void createFarBackground();
};
#endif