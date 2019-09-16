#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Square{

private:
    int _side;
    int _x,_y;
    int _r,_g,_b,_a;
    
    SDL_Rect _rectangle;
    SDL_Texture* _texture = nullptr;
    SDL_Renderer* _renderer = nullptr;

public:
    Square(SDL_Renderer* renderer, int side, int x, int y, int r, int g, int b, int a);
    Square(SDL_Renderer* renderer, int side, int x, int y, std::string &image_path);
    ~Square();

    void display();

private:
    void raiseException(std::string mesage);
};