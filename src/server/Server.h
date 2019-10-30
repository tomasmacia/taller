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
    void setToBroadcast(std::string message);               //usada por objetos del modelo
    void setToSendToSpecific(std::string message,int connectionID);   //usada por objetos del modelo


    //SOLO PUEDE USAR EL UserConnection
    int send(std::string, int someSocketFD);         //SOLO ACCEDIDO DESDE EL SENDTHREAD DE USER CONNECTION
    std::string receive(int someSocketFD);                  //SOLO ACCEDIDO DESDE EL READTHREAD DE USER CONNECTION

private:
    std::mutex mu;
    bool serverOn;

    int maxBytesBuffer;
    int maxConnections;

    int socketFD;
    std::map<int,UserConnection*> connections;
    int nextConectionIDtoAssign = 0;

    void error(const char* msg);
    std::string parse(char* rawRecivedMessage);

    //no podemos permitir que toquen esto desde afuera
    //===============
    void listenThread();
    void specificSend(std::string message,int connectionID);    //usada para hablar con los UserConnections

    bool init();
    int create();
    int bind();
    int listen();                                  //SOLO ACCEDIDO DESDE EL LISTENTHREAD DE USER CONNECTION
    int accept();                                  //SOLO ACCEDIDO DESDE EL LISTENTHREAD DE USER CONNECTION
    int shutdown();
    int close();
};


#endif //GAME_SERVER_H
