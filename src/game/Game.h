#ifndef GAME_H_
#define GAME_H_

#include "Controller.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/config.h"

class Game {
public:

    virtual void start() = 0;

    // *************************
    // ******* METHODS *********
    // *************************

    void end();

    // *************************
    // ******* WRAPPERS ********
    // *************************

    Config* getConfig() {
        return config;
    }

    Controller* getController() {
        return controller;
    }

protected:
    virtual void init() = 0;
    virtual void destroy() = 0;

    virtual void initController();
    void initConfig();

    bool isRunning;

    Controller *controller = nullptr;
    Config *config = nullptr;
};

#endif