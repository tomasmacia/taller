//
// Created by axel on 29/10/19.
//

#ifndef GAME_IDCOMPONENT_H
#define GAME_IDCOMPONENT_H

#include "../../to_remove_or_modify/ECS.h"

class IDComponent : public Component{

public:
    IDComponent(int id);

    int getId();
    void setNewID(int newID);

private:
    int id = 0;

};


#endif //GAME_IDCOMPONENT_H
