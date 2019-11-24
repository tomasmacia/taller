#include "IAComponent.h"
#include "StateComponent.h"

IAComponent::IAComponent(){
    srand (time(NULL));
}

void IAComponent::update(){
    auto state = entity->getComponent<StateComponent>();

    if (counter >= CHOOSING_ACTION_DELAY){
        _currentAction = generateAction();
        counter = 0;
        if (side == 1){
            side ++;
        } else {
            side =1;
        }
    }
    state->setIncomingAction(_currentAction);
    counter++;
}

Action IAComponent::generateAction(){
  if (side == 1){
      return RIGHT;
  } else {
      return LEFT;
  }
}