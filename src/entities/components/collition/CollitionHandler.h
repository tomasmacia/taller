//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONHANDLER_H
#define GAME_COLLITIONHANDLER_H


#include "../Position.h"
#include "CollitionBox.h"
#include "../../../game/CollitionManager.h"
#include "../../../net/messaging/Sendable.h"

using namespace std;

class CollitionHandler {

public:
    CollitionHandler(CollitionManager* collitionManagel);
    virtual ~CollitionHandler();

    void addCollitionBox(CollitionBox* collitionBox);
    void dragToRight(int amount);
    void setOwnerToAllCollitionBox(Entity* owner);

    void eraseCollitionBoxes();

    bool hasVisualCollitionBox();
    void setToAllCollitionBoxScreenPosition(ScreenPosition *pPosition);

    list<Sendable*> generateSendable();

protected:
    CollitionManager* _collitionManager = nullptr;

    list<CollitionBox*>* _collitionBoxes = nullptr;
};


#endif //GAME_COLLITIONHANDLER_H