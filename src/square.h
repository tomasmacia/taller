#include <SDL2/SDL.h>

class Square{
    //Square seria cody, podria ser hija de una clase madre personaje 
    //de la que heredan tmb los enemigos u objetos rompibles

private:
    int _side;
    int _x,_y;
    
    SDL_Rect _rectangle;

public:
    Square(int side, int x, int y);
    void move(bool movLft,bool movRgth, bool movUp, bool movDwn);
    const SDL_Rect getPosition();
};