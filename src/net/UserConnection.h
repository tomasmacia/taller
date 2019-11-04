//
// Created by Tomás Macía on 27/10/2019.
//

#ifndef GAME_USERCONNECTION_H
#define GAME_USERCONNECTION_H

#include "Server.h"
#include <mutex>
#include <thread>
#include "../game/MessageParser.h"
#include "../game/ObjectSerializer.h"

// UserConnection at Server level
class UserConnection {
public:
    UserConnection(int socket, int userId, Server *server,GameServer* gameServer);

    //API
    //===============================
    void setToSendMessage(std::string message);
    void init();
    bool connectionOff();

    //GETTERS
    //===============================
    int getId(){
        return  userId;
    }

private:

    //THREADS
    //===============================
    void readThread();
    void sendThread();
    void dispatchThread();

    //DISPATCHING INCOMING MESSAGES
    //===============================
    void processLoginFromTheClient(std::string msg);
    void processInput(std::string msg);

    //DISCONECTION RELATED
    //===============================
    void kill();

    //ATRIBUTES
    //===============================
    std::mutex sendQueueMutex;
    std::mutex incomingQueueMutex;
    int socketFD;
    int userId;

    Server *server = nullptr;
    GameServer* gameServer = nullptr;
    MessageParser messageParser;
    ObjectSerializer objectSerializer;

    list<string> toSendMessagesQueue;
    list<string> incomingMessagesQueue;
};


#endif //GAME_USERCONNECTION_H
