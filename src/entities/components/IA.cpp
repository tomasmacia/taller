#include <ctime>
#include <cstdlib>
#include <utility>
#include "IA.h"
#include "AttackingBehavior.h"
#include "PatrolBehavior.h"
#include "PursuitBehavior.h"
#include "../../utils/MapUtils.h"

IA::IA(EntityManager* em, Position* subjectPosition) {
    srand (time(nullptr));
    auto *patrolBehavior = new PatrolBehavior(this, em, subjectPosition);
    auto *pursuitBehavior = new PursuitBehavior(nullptr, this, em, subjectPosition);
    auto *attackingBehavior = new AttackingBehavior(this, em, subjectPosition);

    this->behaviors.emplace(std::make_pair(PATROL, patrolBehavior));
    this->behaviors.emplace(std::make_pair(TARGET, pursuitBehavior));
    this->behaviors.emplace(std::make_pair(ATTACKING, attackingBehavior));

    this->behavior = patrolBehavior;
    this->em = em;
}

void IA::update(){
    this->behavior->update();
}

Action IA::getNext(){
    return this->behavior->getNext();
}

void IA::changeBehavior(Will* newBehavior){
    delete this->behavior;
    this->behavior = newBehavior;
}

void IA::switchBehavior(EnemyBehaviorType enemyBehaviorType) {
    this->behavior = MapUtils::getOrDefault(behaviors, enemyBehaviorType, this->behavior);
}

IA::~IA() {
    for( auto const& [key, val] : this->behaviors ) {
        delete(val);
    }
}