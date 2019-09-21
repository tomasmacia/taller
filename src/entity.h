#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "position.h"
#include "appearance.h"
#include "sprite_parser.h"

class Entity{   //REPRESENTA Y ENGLOBA EL ASPECTO FISICO DE UNA COSA
                //posicion, apariencia, tamaño, movimiento, animacion

private:

    float SPEED_CONSTANT = 0.3;

    float _velocity_x = 0;
    float _velocity_y = 0;

    bool animationRunning = false;

    SpriteParser* _spriteParser = nullptr;
    Position* _position = nullptr;
    Appearance* _appearance = nullptr; //esta fuertemente ligada a la posicion

public:
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::vector <std::string>& spritePaths);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::string& spritePath);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y);
    ~Entity();

    void handeEvent(SDL_Event e);
    void move();
    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    void updateImage();

private:
    void raiseException(std::string mesage);
};