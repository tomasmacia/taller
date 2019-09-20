#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "position.h"
#include "square.h"
#include "sprite_parser.h"

class Entity{

private:

    float SPEED_CONSTANT = 0.3;

    float _velocity_x = 0;
    float _velocity_y = 0;

    SpriteParser* _spriteParser;
    Position* _position;
    Square* _square; //es la apariencia y esta fuertemente relacionada a la posicion

public:
    Entity(SDL_Renderer* renderer, float side, float x, float y, int r, int g, int b, int a);
    Entity(SDL_Renderer* renderer, float side, float x, float y, std::vector <std::string>& spritePaths);
    ~Entity();

    void handeEvent(SDL_Event e);
    void move();

    void update();
    void display();

private:
    void raiseException(std::string mesage);
};