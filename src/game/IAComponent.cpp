#include "IAComponent.h"
#include "StateComponent.h"

void IAComponent::update(){
    auto state = entity->getComponent<StateComponent>();
    state->setIncomingAction(generateAction());
}

Action IAComponent::generateAction(){
  srand (time(NULL));
  int n = rand() % 4;

    switch (n) {
        case 0:
            return NONE;
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