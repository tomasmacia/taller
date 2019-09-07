#include "iostream"

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