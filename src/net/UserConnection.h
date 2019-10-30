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
    UserConnection(int socket, int userId, Server *server,GameServer* gameServer);

    void setToSendMessage(std::string message);
    void init();

private:
    int socketFD;
    GameServer* gameServer = nullptr;

    int userId;
    bool connectionIsOn;


    char SEPARATOR = '_';
    std::string END_SERIALIZATION_SIMBOL = "x";
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
    void dispatchThread();

    void connectionLost();
    bool connectionOff();

    void processLoginFromTheClient(std::string msg);
    void processInput(std::string msg);
    const vector<string> split(const string& s, const char& c);
};


#endif //GAME_USERCONNECTION_H
