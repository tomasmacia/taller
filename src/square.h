#include <SDL2/SDL.h>

class Square{

private:
    int _side;
    int _x,_y;
    int _r,_g,_b,_a;
    
    SDL_Rect _rectangle;

public:
    Square(int side, int x, int y, int r, int g, int b, int a);

    void display();
    void move(bool movLft,bool movRgth, bool movUp, bool movDwn);
};