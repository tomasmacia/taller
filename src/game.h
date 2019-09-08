#include "iostream"
#include "window.h"

class Game
{
public:
/*Constructor*/
	Game();
    //Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ 4 ];
SDL_Texture* gSpriteSheetTexture;

private:
    class Window* _gwindow;
    void initialize();
    void runLoop();
/*Destructor*/
    ~Game();
};