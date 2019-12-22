//
// Created by Tomás Macía on 16/10/2019.
//

#ifndef GAME_INPUTPOLLER_H
#define GAME_INPUTPOLLER_H

#include <list>
#include "../../enumerates/Action.h"
#include "../../game/Controller.h"
#include "ID.h"
#include "Will.h"


class InputPoller : public Will {
public:
    InputPoller(Controller* controller, ID* id);

    void update() override ;
    Action getNext() override;

    ~InputPoller() override {

    }

private:
    void selectAndStoreInputsFromIncoming(std::list<std::tuple<Action,int>>& inputs);

    std::list<std::tuple<Action,int>> playerInputs;

    Controller* _controller = nullptr;
    ID* _id = nullptr;
};


#endif //GAME_INPUTPOLLER_H
