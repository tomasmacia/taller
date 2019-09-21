#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Appearance{

private:
    int _r,_g,_b,_a;

    SDL_Rect _rectangle;
    SDL_Texture* _texture = nullptr;
    SDL_Renderer* _renderer = nullptr;

public:
    Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a);
    Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, std::string image_path);
    Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, SDL_Texture* texture);
    ~Appearance();

    void setX(float x);
    void setY(float y);

    void loadImage(std::string newImagePath);    //DOES NOT ACTUALLY LOAD INTO MEMORY
    void updateImage();

private:

    void raiseException(std::string mesage);
};
#endif