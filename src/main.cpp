#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include "window.h"
#include "square.h"

int main( int argc, char* args[] ){

    std::string TITLE = "un titulo lindo";

    Window window(TITLE,800,600);
    SDL_Renderer* renderer = window.getRenderer();
    Square square(renderer,40,400,300,255,0,0,255);


    SDL_Event e;
    while(!window.isClosed()){
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if(( e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                window.close();
            }
        }
        window.display();
        square.display();
        window.showAll();
    }

    return 0;
}
