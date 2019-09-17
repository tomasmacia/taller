
#include "Updateable.h"
#include "Displayable.h"
#include "Controller.h"
#include <vector>

#ifndef GAME_H_
#define GAME_H_

class Game{

private:

    bool end;
    std::vector<Updateable*> updateables;
    std::vector<Displayable*> displayables;
    void readInput();

public:

    Game();
    void setup();
    void start();
    void addUpdateable(Updateable* newUpdateable);
    void addDisplayable(Displayable* newDisplayable);
    bool endCondition();
};

#endif