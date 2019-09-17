#include "window.h"
#include "square.h"
#include "Game.h"

// void pollEvents(Window &window,Square &square){ //HARDCODEADO
//     SDL_Event event;

//     if (SDL_PollEvent(&event)){
//         square.pollEvents(event);
//         window.pollEvents(event);
//     }
// }
  
int main(int argc, char** argv) { 

    Window* window = new Window("titulo",800,600);
    Square* square = new Square(100, 400, 300, 200, 0, 200, 255);

    // while (!window.isClosed()){
    //     pollEvents(window, square);
    //     square.display();
    //     window.display();
    // }
    // return 0; 
    Game game;
    game.setup();
    game.addDisplayable(square);
    game.addUpdateable(square);
    game.addDisplayable(window);
    game.addUpdateable(window);
    game.start();


} 
