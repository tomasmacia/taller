using namespace std; 

#include <iostream> 
#include <string>
#include "game.h"

  
int main(int argc, char** argv) { 

   Game* game = new Game(800,600);
    //std::cout <<"llegue" << "\n";
   int i = 1;
   while (!game->isClosed()){
        //std::cout <<"frame number: "<< i << "\n";
       //game->handleEvents();
       game->runLoop();
       //i++;
   }
   delete(game);
    return 0;
} 
