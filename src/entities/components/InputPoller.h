//
// Created by Tomás Macía on 16/10/2019.
//

#ifndef GAME_INPUTPOLLER_H
#define GAME_INPUTPOLLER_H

#include <list>
#include <mutex>
#include "../../enumerates/Action.h"
#include "Will.h"


class InputPoller : public Will {
public:
    void update() override {}
    void set(Action action);
    Action getNext() override;

    ~InputPoller() override = default;

private:
    //void selectAndStoreInputsFromIncoming(std::list<std::tuple<Action,int>>& inputs);

    std::mutex mu;

    std::list<Action> playerInputs;
};


#endif //GAME_INPUTPOLLER_H
