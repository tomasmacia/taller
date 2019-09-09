#include <SDL2/SDL.h>

class Cody{
    //Square seria cody, podria ser hija de una clase madre personaje 
    //de la que heredan tmb los enemigos u objetos rompibles

private:
    int _x,_y,_w,_h;
    
    SDL_Rect _rectangle;

public:
    
    Cody( int x, int w, int h);
    void move(bool movLft,bool movRgth, bool movUp, bool movDwn);
    const SDL_Rect getPosition();
};