#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "position.h"
#include "appearance.h"
#include "sprite_parser.h"

class Entity{   //REPRESENTA Y ENGLOBA EL ASPECTO FISICO DE UNA COSA
                //posicion, apariencia, tamaño, movimiento, animacion

private:

    //FOR MOVEMENT
    float SPEED_CONSTANT = 0.3;
    float _velocity_x = 0;
    float _velocity_y = 0;

    //FOR PERSPECTIVE
    bool _perspectiveSensible = false;
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

    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a, float minScaleFactor, float maxY, float minY);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, std::vector <Sprite*>* sprites, float minScaleFactor, float maxY, float minY);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite, float minScaleFactor, float maxY, float minY);
    Entity(SDL_Renderer* renderer, float width, float height, float x, float y, float minScaleFactor, float maxY, float minY);
    ~Entity();

    void handeEvent(SDL_Event e);
    void move();
    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    float getY();

    void updateImage();

private:
    void initPerspectiveParameters(float width, float height, float minScaleFactor, float maxY, float minY);
    float applyPerspectiveTransformationTo(float length, float y);
    void raiseException(std::string mesage);
    void changeXBy(float amount);
    void changeYBy(float amount);
    void applyPersepective();
};