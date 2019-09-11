
#include "Updateable.h"
#include "Displayable.h"
#include "Controller.h"
#include <list>

#ifndef GAME_H_
#define GAME_H_

class Game{

private:

    bool end;
    std::list <Updateable> updateables;
    std::list <Displayable> displayables;
    void readInput();

public:

    void setup();
    void start();
    void addUpdateable(Updateable newUpdateable);
    void addDisplayable(Displayable newDisplayable);
    bool endCondition();
};

#endif