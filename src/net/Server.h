//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <fcntl.h>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <thread>
#include <mutex>
#include "../game/GameServer.h"
#include "messaging/MessageParser.h"
#include "messaging/ObjectSerializer.h"

class GameServer;
class UserConnection;

class Server {
public:
    Server(GameServer* gameServer);
    ~Server();

    //API
    //===============================
    void init();
    int numberOfConectionsEstablished();
    void setToSendToSpecific(std::string message,int connectionID);
    void setToBroadcast(std::string message);
    void removeConnection(int id);
    void stopListening();
    int close();
    void client_noBlock(int socket);

    
    //ACTUAL DATA TRANSFER
    //===============================
    int send(std::string, int someSocketFD);
    string receive(int someSocketFD);

    //THREADS
    //===============================
    void listenThread();
    

private:
    //INIT
    //===============================
    int create();
    int bind();
    void setToNonBlocking();
    int listen();
    int accept();
    UserConnection* addNewConnection(int newSocketFD);

    //ERROR
    //===============================
    void error(string msg);

    //DISCONECTION RELATED
    //===============================
    int shutdown();

    //ATRIBUTE
    //===============================
    bool serverOn;
   

    int maxBytesBuffer;
    int maxConnections;

    int MAX_PENDING_CONNECTIONS = 6;

    GameServer* gameServer = nullptr;
    MessageParser messageParser;
    ObjectSerializer *objectSerializer = nullptr;

    int nextConectionIDtoAssign = 0;
    int socketFD;
    std::vector<std::thread> connectionThreads;
    std::map<int,UserConnection*> connections;
    std::map<int,int> socketIDMap;

    void beginDisconectionWith(int id);

    void printMovement(char buff[2500]);
};


#endif //GAME_SERVER_H
