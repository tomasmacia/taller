//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_SCOREAPPEARANCE_H
#define GAME_SCOREAPPEARANCE_H


#include "Appearance.h"
#include "../../Score.h"


class ScoreAppearance : public Appearance{

public:
    ScoreAppearance(Score* score);

    void update();

private:
    Score* score = nullptr;
};


#endif //GAME_SCOREAPPEARANCE_H
