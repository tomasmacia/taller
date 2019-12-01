//
// Created by axel on 24/11/19.
//

#include "Enemy.h"

Enemy::Enemy(Will *will, State *state, AnimatedEntityCollitionHandler *collitionHandler, Position *position,
             Physics *physics, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
             Damage *damage, Life *life, ID *id, Score *score, ScoreAppearance *scoreAppearance) :

             AnimatedEntity(will, state, collitionHandler, position, physics, screenPosition, appearance, sound, damage, life, attack){

}

int Enemy::setAttackedWith(AttackCode attack) {

    int damageInflicted = damage->enemyAttackedWith(attack);

    life->decreseBy(damageInflicted);

    if (lifeEmpty()){
        return score->enemyKilled();
    }
    else{
        return score->enemyAttackedWith(attack);
    }
}
