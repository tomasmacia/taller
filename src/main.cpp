using namespace std; 

#include <iostream> 
#include <string>
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

    std::string image_path = "duck.jpg";
    Window window("titulo",800,600);
    Square square(100, 400, 300,image_path);

    while (!window.isClosed()){
        pollEvents(window, square);
        square.display();
        window.display();
    }
    return 0; 
} 
