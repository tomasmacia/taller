using namespace std; 

#include <iostream> 
#include "game.h"
#include <vector>
  
int main(int argc, char** argv) { 

   Game* game = new Game(800,600);
    return 0;

} 

void level1(){
    std::vector< string> g1;
    g1.push_back("Sprites/FF_Stage4_floor6.png");
    g1.push_back("Sprites/FF_Stage4_floor5.png");
    g1.push_back("Sprites/FF_Stage4_floor4.png");
    g1.push_back("Sprites/FF_Stage4_floor3.png");
    g1.push_back("Sprites/FF_Stage4_floor2.png");
    g1.push_back("Sprites/FF_Stage4_floor1.png");

    for(int i=0;i<6;i++){
       std::cerr<<g1[i]<<std::endl;
    }
    
}