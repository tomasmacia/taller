#include "IAComponent.h"
#include "State.h"

IAComponent::IAComponent(){
    srand (time(NULL));
}

void IAComponent::update(){
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

Action IAComponent::generateAction(){
  if (side == 1){
      return RIGHT;
  } else {
      return LEFT;
  }
}