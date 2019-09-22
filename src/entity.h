#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "position.h"
#include "appearance.h"
#include "sprite_parser.h"

class Entity{   //REPRESENTA Y ENGLOBA EL ASPECTO FISICO DE UNA COSA
                //posicion, apariencia, tamaño, movimiento, animacion

//IMPORTANTE: EL SISTEMA DE COORDENADAS QUE MANEJA ENTITY ES
//            DISTINTO AL QUE MANEJA SDL Y APPERARANCE.
//            EL SISTEMA COORDENADO DE ENTITY ES EL QUE SE MANEJA
//            EN LA LOGICA DEL JUEGO

private:

    //FOR MOVEMENT
    float X_SPEED_CONSTANT = 0.4; //MUST BE POSITIVE
    float Y_SPEED_CONSTANT = 0.3; //MUST BE POSITIVE
    float _velocity_x = 0;
    float _velocity_y = 0;

    //FOR PERSPECTIVE
    bool _perspectiveSensitive = false;
    float _minScaleFactor;
    float _maxWidth;
    float _maxHeight;
    float _maxY;
    float _minY;

    bool animationRunning = false;

    SpriteParser* _spriteParser = nullptr;
    Position* _position = nullptr;
    Appearance* _appearance = nullptr; //esta fuertemente ligada a la posicion

public: //se que parecen muchos constructores pero es la solucion mas simple. Dado el tiempo que tenemos esto anda y es flexible
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::vector <Sprite*>* sprites);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y);

    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a, float minScaleFactor, float maxY, float minY,bool perspectiveSensitive);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::vector <Sprite*>* sprites, float minScaleFactor, float maxY, float minY, bool perspectiveSensitive);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite, float minScaleFactor, float maxY, float minY, bool perspectiveSensitive);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, float minScaleFactor, float maxY, float minY, bool perspectiveSensitive);
    ~Entity();

    void move();
    void enableLeftXMotion();
    void enableRightXMotion();
    void enableUpYMotion();
    void enableDownYMotion();
    void disableXMotion();
    void disableYMotion();

    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    float getY();
    float getWidth();
    float getHeigth();

    void update();
    void updateImage();

private:
    void initPerspectiveParameters(float width, float height, float minScaleFactor, float maxY, float minY);
    float applyPerspectiveTransformationTo(float length, float y);
    void applyPersepective();
    void changeXBy(float amount);
    void changeYBy(float amount);
    float correctXToSDLCoordinateSystem(float width, float height,float previousX);
    float correctYToSDLCoordinateSystem(float width, float height,float previousY);
    void initAppearance(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a);
    void initAppearance(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite);
    void initPosition(float x, float y);
    void raiseException(std::string mesage);
};
#endif