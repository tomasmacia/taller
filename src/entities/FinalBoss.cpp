//
// Created by axel on 24/11/19.
//

#include "FinalBoss.h"

//
// Created by axel on 24/11/19.
//

#include "Enemy.h"

FinalBoss::FinalBoss(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
             State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, Will *will,
             Physics *physics, Attack *attack)

        : AnimatedEntity(collitionHandler, life, damage, score, position, state, screenPosition, appearance,
                         sound, will, physics, attack) {

    this->life->initializeWith(FINAL_BOSS_LIFE_AMOUNT);
}

int FinalBoss::setAttackedWith(AttackCode attack) {

    AnimatedEntity::setAttackedWith(attack);
    int damageInflicted = damage->enemyAttackedWith(attack);

    life->decreseBy(damageInflicted);

    if (lifeEmpty()){
        return score->finalBossKilled();
    }
    else{
        return score->enemyAttackedWith(attack);
    }
}