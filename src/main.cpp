using namespace std; 

#include <iostream> 
#include <string>
#include "game.h"

  
int main(int argc, char** argv) { 

   Game* game = new Game(800,600);

   int i = 1;
   while (!game->isClosed()){
       //std::cout <<"frame number: "<< i << "\n";
       game->runLoop();
       //i++;
   }
    return 0;
} 
