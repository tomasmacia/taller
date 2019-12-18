#ifndef GAME_IA_H
#define GAME_IA_H

#include "../../enumerates/Action.h"
#include "Will.h"
#include <list>
#include <map>
#include "EnemyBehaviorType.h"
#include "../game/EntityManager.h"

class IA : public Will {
public:
    IA(EntityManager* em,Position* subjectPosition);
    void update() override;
    Action getNext() override;
    void changeBehavior(Will* newBehavior);
    void switchBehavior(EnemyBehaviorType);

    Will* getCurrentBehavior() {
        return behavior;
    }

    void setFinalBoss(bool finalBoss) {
        this->isFinalBoss = finalBoss;
    }

    bool finalBoss() {
        return this->isFinalBoss;
    }

    ~IA() override;

private:

    Action _currentAction = NONE;
    int CHOOSING_ACTION_DELAY = 50;
    int counter = 0;
    int side = 1;
    Will* behavior;
    std::map<EnemyBehaviorType, Will*> behaviors;
    EntityManager* em;
    bool isFinalBoss;
};

#endif //GAME_IA_H
