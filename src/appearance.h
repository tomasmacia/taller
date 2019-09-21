#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"

class Appearance{

private:
    //DEFAULT COLOR WHEN NO IMAGEN LOADED *MAGENTA*
    int _r = 255;
    int _g = 0;
    int _b = 255;
    int _a = 255;

    SDL_Rect _rectangle;
    SDL_Texture* _texture = nullptr;
    SDL_Renderer* _renderer = nullptr;

public:
    Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a);
    Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite);
    Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, SDL_Texture* texture);
    ~Appearance();

    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);
    float getWidth();
    float getHeigth();

    void loadImage(Sprite* sprite);
    void updateImage();

private:

    void raiseException(std::string mesage);
};
#endif