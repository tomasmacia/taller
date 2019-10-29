//
// Created by axel on 28/10/19.
//

#ifndef GAME_IDPLAYER_H
#define GAME_IDPLAYER_H

class IDPlayer { //cada pc tiene asignado un player id y es unico

public:
    void addNewPlayer();
    int getNewIdPlayer();

private:
    int lastIDGenerated = 1; //el cero esta reservado para el NULL
};

#endif //GAME_IDPLAYER_H
