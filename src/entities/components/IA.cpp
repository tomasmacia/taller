#include <ctime>
#include <cstdlib>
#include "IA.h"
#include "State.h"

IA::IA(){
    srand (time(nullptr));
}

void IA::update(){

    if (counter >= CHOOSING_ACTION_DELAY){
        counter = 0;
        if (side == 1){
            side ++;
        } else {
            side =1;
        }
    }
    counter++;
}

Action IA::getNext(){
  if (side == 1){
      return RIGHT;
  } else {
      return LEFT;
  }
}