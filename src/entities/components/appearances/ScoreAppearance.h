//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_SCOREAPPEARANCE_H
#define GAME_SCOREAPPEARANCE_H


#include "Appearance.h"

class Score;
class ScoreAppearance : public Appearance{

public:
    ScoreAppearance(ScreenPosition *screenPosition, Score *score);
    Renderable* actuallyGenerateRenderable() override ;
    void loadNextImage() override ;

    void update();

private:
    Score* score = nullptr;
};


#endif //GAME_SCOREAPPEARANCE_H
