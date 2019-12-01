//
// Created by axel on 24/11/19.
//

#ifndef GAME_SCORE_H
#define GAME_SCORE_H


#include "components/appearances/ScoreAppearance.h"

class Score {

public:
    void increaseBy(int amount);

private:
    int current = 0;

};


#endif //GAME_SCORE_H
