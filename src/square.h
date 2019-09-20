#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Square{

private:
    int _r,_g,_b,_a;

    SDL_Rect _rectangle;
    SDL_Texture* _texture;
    SDL_Renderer* _renderer;

public:
    Square(SDL_Renderer* renderer, float side, float x, float y, int r, int g, int b, int a);
    Square(SDL_Renderer* renderer, float side, float x, float y, std::string& image_path);
    Square(SDL_Renderer* renderer, float side, float x, float y, SDL_Texture* texture);
    ~Square();

    void setX(float x);
    void setY(float y);

    void display();

private:
    void raiseException(std::string mesage);
};
#endif