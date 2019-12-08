#include <ctime>
#include <cstdlib>
#include "IA.h"
#include "State.h"
#include "PatrolBehavior.h"

IA::IA(EntityManager* em,Position* subjectPosition){
    srand (time(nullptr));
    this->behavior = new PatrolBehavior(this,em,subjectPosition);
    this->em = em;
}

void IA::update(){
    this->behavior->update();
}

Action IA::getNext(){
    this->behavior->getNext();
}

void IA::changeBehavior(Will* newBehavior){
    delete this->behavior;
    this->behavior = newBehavior;
}