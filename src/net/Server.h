//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <list>
#include <map>
#include <mutex>

class UserConnection;

class Server {
public:
    Server();
    ~Server();

    //API
    void setToBroadcast(std::string message);                         //LO QUE VE EL MODELO
    void setToSendToSpecific(std::string message,int connectionID);   //LO QUE VE EL MODELO
    bool init();
    void initialListeningToClients();

    //SOLO PUEDE USAR EL UserConnection
    int send(std::string, int someSocketFD);         //SOLO ACCEDIDO DESDE EL SENDTHREAD DE USER CONNECTION
    std::string receive(int someSocketFD);                  //SOLO ACCEDIDO DESDE EL READTHREAD DE USER CONNECTION

    //THREADS
    //===============
    void listenThread();

private:
    std::string END_SERIALIZATION_SIMBOL = "x";

    std::mutex mu;
    bool serverOn;
    char* buffer;

    int maxBytesBuffer;
    int maxConnections;

    int socketFD;
    std::map<int,UserConnection*> connections;
    int nextConectionIDtoAssign = 0;

    void error(const char* msg);
    std::string extractMessageFromStream();

    //no podemos permitir que toquen esto desde afuera
    //===============
    int create();
    int bind();
    int listen();                                  //SOLO ACCEDIDO DESDE EL LISTENTHREAD DE USER CONNECTION
    int accept();                                  //SOLO ACCEDIDO DESDE EL LISTENTHREAD DE USER CONNECTION
    int shutdown();
    int close();
};


#endif //GAME_SERVER_H
