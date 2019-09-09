#include "iostream"
#include "window.h"

class Game
{
public:
/*Constructor*/
	Game(int width, int heigth);
    
private:
    class Window* _gwindow;
    void initialize(int width, int heigth);
    void runLoop(int width, int heigth);
/*Destructor*/
    ~Game();
};