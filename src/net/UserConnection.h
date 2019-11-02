//
// Created by Tomás Macía on 27/10/2019.
//

#ifndef GAME_USERCONNECTION_H
#define GAME_USERCONNECTION_H

#include "Server.h"
#include <thread>
#include <mutex>
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

public:

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
    void connectionLost();
    bool connectionOff();

    //ATRIBUTES
    //===============================
    std::mutex mu;
    int socketFD;
    int userId;
    bool connectionIsOn;

    Server *server = nullptr;
    GameServer* gameServer = nullptr;
    MessageParser messageParser;
    ObjectSerializer objectSerializer;

    string incomingMessage;
    string toSendMessage;
    list<string> toSendMessagesQueue;
    list<string> incomingMessagesQueue;
};


#endif //GAME_USERCONNECTION_H
