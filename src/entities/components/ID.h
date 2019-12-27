//
// Created by axel on 29/10/19.
//

#ifndef GAME_ID_H
#define GAME_ID_H

class ID{

public:
    ID(int id);

    int get();
    void setNew(int newID);

private:
    int id = 0;

};


#endif //GAME_ID_H
