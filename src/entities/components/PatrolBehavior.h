#ifndef GAME_PATROLBEHAVIOR_H
#define GAME_PATROLBEHAVIOR_H

#include "IA.h"
#include "../Character.h"
#include "PursuitBehavior.h"


const int SIDE_CHANGE_DELAY = 60;
const int PLAYER_DETECTION_DELAY = 30;
const int PLAYER_DETECTION_RANGE = 2000;


class PatrolBehavior : public Will{
    public:
        PatrolBehavior(IA* owner, EntityManager* manager, Position* subjectPosition);
        void update() override;
        Action getNext() override;

        ~PatrolBehavior() override {

        }

    private:

        int sideChangeCounter = 0;
        int playerDetectCounter = 0;
        int side = 1;
        IA* owner;
        bool playerDetected = false;
        Character* target;
        EntityManager* manager;
        Position* subjectPosition;

        void checkForNearbyPlayer();
        Character *getNearPlayer();

};

#endif