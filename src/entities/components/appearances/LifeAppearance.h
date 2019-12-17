//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_LIFEAPPEARANCE_H
#define GAME_LIFEAPPEARANCE_H


#include "Appearance.h"

class LifeAppearance : public Appearance {

public:
    LifeAppearance(ScreenPosition* screenPosition);

    void update() override;
    Renderable* actuallyGenerateRenderable() override ;
    void loadNextImage() override ;
    //todo
    void hit();
    void noLifes();
    void setYPosition(int a);

private:
    string base = "resources/sprites/score/Blue/100v2.png";
    int golpes=0;
    bool resetLife = true;
    int YPosition;

};


#endif //GAME_LIFEAPPEARANCE_H
