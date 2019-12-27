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
    Renderable* GenerateRenderableToDisconnect(bool disconnectOrDead);
    Renderable* GenerateRenderableToCantLife();
    void loadNextImage() override ;
    //todo
    void hit( int damage);
    void noLifes();
    void setYPosition(int a);
    void setXPosition(int a);
    void pickColor(int a);
    void setLifes(int lifes);



private:
    string base, _lifes;
    string life0,life20,life40,life60,life80,lifecomplete;

    string lifegrey;
    string life20grey,life40grey,life60grey,life80grey,lifecompletegrey;
    int life=100;
    bool resetLife = true;
    int YPosition,XPosition;

};


#endif //GAME_LIFEAPPEARANCE_H
