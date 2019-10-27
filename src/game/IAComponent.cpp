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
    }
    state->setIncomingAction(_currentAction);
    counter++;
}

Action IAComponent::generateAction(){
  int n = rand() % 4 + 1;

    switch (n) {
        case 1:
            return UP;
        case 2:
            return DOWN;
        case 3:
            return LEFT;
        case 4:
            return RIGHT;
    }
}