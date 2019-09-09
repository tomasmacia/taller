#include "iostream"
#include "window.h"

class Game
{
public:
/*Constructor*/
	Game();
    
private:
    class Window* _gwindow;
    void initialize();
    void runLoop();
/*Destructor*/
    ~Game();
};