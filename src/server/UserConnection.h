//
// Created by Tomás Macía on 27/10/2019.
//

#ifndef GAME_USERCONNECTION_H
#define GAME_USERCONNECTION_H

#include "Server.h"
#include <thread>
#include <mutex>

// UserConnection at Server level
class UserConnection {
public:
    UserConnection(int socket, int userId, Server *server);

    void setToSendMessage(std::string message);
    void init();

private:
    int socketFD;

    int userId;
    bool connectionIsOn;

    std::string CONTROL__ID_ON = "*";
    std::string incomingMessage;
    std::string toSendMessage;
    std::list<std::string> toSendMessagesQueue;

    std::list<std::string> incomingMessagesQueue;
    Server *server = nullptr;

    std::mutex mu;
    //THREADS
    //===============
    void readThread();

    void sendThread();
    void connectionLost();
    bool connectionOff();
};


#endif //GAME_USERCONNECTION_H
