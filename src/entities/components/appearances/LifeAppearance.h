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
};


#endif //GAME_LIFEAPPEARANCE_H
