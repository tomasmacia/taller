#include "IA.h"
#include "State.h"

IA::IA(){
    srand (time(NULL));
}

void IA::update(){
    auto state = entity->getComponent<State>();

    if (counter >= CHOOSING_ACTION_DELAY){
        _currentAction = generateAction();
        counter = 0;
        if (side == 1){
            side ++;
        } else {
            side =1;
        }
    }
    state->setIncoming(_currentAction);
    counter++;
}

Action IA::generateAction(){
  if (side == 1){
      return RIGHT;
  } else {
      return LEFT;
  }
}