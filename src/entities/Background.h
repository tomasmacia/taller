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
    Background(BackgroundAppearance* appearance);
    ~Background() override;

    //API
    //===============================
    void update() override ;
    list<Sendable*> generateSendable() override;

private:
    BackgroundAppearance* appearance = nullptr;
};


#endif //GAME_BACKGROUND_H
