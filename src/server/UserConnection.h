//
// Created by Tomás Macía on 27/10/2019.
//

#ifndef GAME_USERCONNECTION_H
#define GAME_USERCONNECTION_H

#include "Server.h"
#include <thread>

// UserConnection at Server level
class UserConnection {
public:
    UserConnection(int socket, int userId, Server *server);

    void init();
private:
    int socketFD;
    int userId;

    Server *server = nullptr;

    std::thread dummy;
    void dummyThread();

    void controlThread();

    void writeThread();
};


#endif //GAME_USERCONNECTION_H
