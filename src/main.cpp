using namespace std; 

#include <iostream> 
#include "window.h"
#include "square.h"

void pollEvents(Window &window,Square &square){ //HARDCODEADO
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        square.pollEvents(event);
        window.pollEvents(event);
    }
}
  
int main(int argc, char** argv) { 

    Window window("titulo",800,600);
    Square square(100, 400, 300, 200, 0, 200, 255);

    while (!window.isClosed()){
        pollEvents(window, square);
        square.display();
        window.display();
    }

    return 0; 
} 