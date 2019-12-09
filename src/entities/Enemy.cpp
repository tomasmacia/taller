//
// Created by axel on 24/11/19.
//

#include "Enemy.h"

Enemy::Enemy(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
             State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, Will *will,
             Physics *physics, Attack *attack, int w, int h, int d)

             : AnimatedEntity(collitionHandler, life, damage, score, position, state, screenPosition, appearance,
                                sound, will, physics, attack,w,h,d) {

    this->life->initializeWith(ENEMY_LIFE_AMOUNT);
}

int Enemy::setAttackedWith(AttackCode attack) {

    if (state->current() != BEING_ATTACKED){

        AnimatedEntity::setAttackedWith(attack);
        int damageInflicted = damage->enemyAttackedWith(attack);

        life->decreseBy(damageInflicted);

        if (lifeEmpty()){
            return score->enemyKilled();
        }
        else{
            return score->enemyAttackedWith(attack);
        }
    }
}
