//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <list>
#include <map>
#include <thread>
#include <mutex>
#include "../game/GameServer.h"
#include "../game/MessageParser.h"
#include "../game/ObjectSerializer.h"

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

    //ACTUAL DATA TRANSFER
    //===============================
    int send(std::string, int someSocketFD);
    std::string receive(int someSocketFD);

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
    UserConnection* accept();

    //ERROR
    //===============================
    void error(const char* msg);

    //DISCONECTION RELATED
    //===============================
    int shutdown();
    int close();

    //ATRIBUTE
    //===============================
    bool serverOn;
    char* buffer;

    int maxBytesBuffer;
    int maxConnections;

    GameServer* gameServer = nullptr;
    MessageParser messageParser;
    ObjectSerializer objectSerializer;

    int nextConectionIDtoAssign = 0;
    int socketFD;
    std::vector<std::thread> connectionThreads;
    std::map<int,UserConnection*> connections;

};


#endif //GAME_SERVER_H
