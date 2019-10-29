//
// Created by axel on 29/10/19.
//

#ifndef GAME_IDCOMPONENT_H
#define GAME_IDCOMPONENT_H

#include "ECS.h"

class IDComponent : public Component{

public:
    IDComponent(int id);

    int getId();

private:
    int id = 0;

};


#endif //GAME_IDCOMPONENT_H
