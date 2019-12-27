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
    list<Sendable *>  numerRenderabls(int score,list<Sendable *> sendables );
    
    void setPositionYSCore(int a){
        positionYscore =a;
    };


    void setPositionXSCore(int a){
        positionXscore =a;
    };
    void update() override;

private:
    Score* score = nullptr;
    int positionYscore,positionXscore;

};


#endif //GAME_SCOREAPPEARANCE_H
