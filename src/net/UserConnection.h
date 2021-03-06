//
// Created by Tomás Macía on 27/10/2019.
//

#ifndef GAME_USERCONNECTION_H
#define GAME_USERCONNECTION_H

#include "Server.h"
#include <mutex>
#include <thread>
#include "messaging/MessageParser.h"
#include "messaging/ObjectSerializer.h"

// UserConnection at Server level
class UserConnection {
public:
    UserConnection(int socket, int userId, Server *server,GameServer* gameServer);

    //API
    //===============================
    void setToSendMessage(std::string message);
    void start();
    bool connectionOff();
    void shutdown();
    bool hasPassedLogin();
    void directSend(string message);
    void setConnectionOff();

    //GETTERS
    //===============================
    int getId(){
        return  userId;
    }
    
    int getSock(){
        return socketFD;
    }
private:

    //THREADS
    //===============================
    void readThread();
    void sendThread();
    void dispatchThread();
    //start tambien es un thread

    //DISPATCHING INCOMING MESSAGES
    //===============================
    void processLoginFromTheClient();
    void processInput();
    void processTestMode();

    //DISCONECTION RELATED
    //===============================
    void checkConnection();
    void kill();
    bool isConnected();

    //ATRIBUTES
    //===============================
    bool connectionOn = true;

    std::mutex sendQueueMutex;
    std::mutex incomingQueueMutex;
    std::mutex isConnectedMutex;
    
    int userId;
    int socketFD;

    Server *server = nullptr;
    GameServer* gameServer = nullptr;
    MessageParser messageParser;
    ObjectSerializer *objectSerializer = nullptr;

    list<string> toSendMessagesQueue;
    list<string> incomingMessagesQueue;
};


#endif //GAME_USERCONNECTION_H
