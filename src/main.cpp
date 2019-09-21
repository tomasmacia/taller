#include <iostream> 
#include <string>
#include "game.h"

  
int main(int argc, char** argv) { 

   Game* game = new Game(800,600);

   while (!game->isClosed()){
        game->handleInput();
        game->update();
        game->display();
   }
   delete(game);
   return 0;
} 
//std::cout <<"llegue" << "\n";
//std::cout <<"frame number: "<< i << "\n";
//game->handleEvents();
//int i = 1;
//i++;
