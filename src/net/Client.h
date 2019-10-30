//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <list>
#include <string>
#include <mutex>

class Client {
public:
    Client();
    ~Client();

    //API
    //===============
    void setToSend(std::string message);
    std::string pollMessage();

private:
    std::string END_SERIALIZATION_SIMBOL = "x";

    int socketFD;
    std::mutex mu;
    bool clientOn;

    int maxBytesBuffer;
    char* buffer;

    std::string incomingMessage;
    std::string toSendMessage;
    std::list<std::string> toSendMessagesQueue;
    std::list<std::string> incomingMessagesQueue;


    int send(std::string msg);                  //SOLO ACCEDIDO DESDE EL SENDTHREAD DE USER CONNECTION
    std::string receive();                  //SOLO ACCEDIDO DESDE EL READTHREAD DE USER CONNECTION

    void error(const char* msg);
    std::string extractMessageFromStream();
    bool connectionOff();


    //THREADS
    //===============
    void readThread();
    void sendThread();

    //no podemos permitir que toquen esto desde afuera
    //===============
    bool init();
    int create();
    int connectToServer();
    int disconnectFromServer();
};


#endif //GAME_CLIENT_H
