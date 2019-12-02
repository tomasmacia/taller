//
// Created by axel on 28/11/19.
//

#ifndef GAME_BACKGROUND_H
#define GAME_BACKGROUND_H


#include "entityHierarchy/Entity.h"
#include "components/appearances/BackgroundAppearance.h"
#include "components/collition/BackgroundCollitionHandler.h"
#include "Screen.h"

class Background : public Entity{

public:
    Background(Screen *screen, string spritePath, float parallaxSpeed, CollitionManager *collitionManager, list<CollitionBox*>* collitionBoxes);
    ~Background();

    //API
    //===============================
    void update() override ;
    Sendable* generateSendable() override;

private:
    BackgroundAppearance* appearance = nullptr;
};


#endif //GAME_BACKGROUND_H
