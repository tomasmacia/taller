//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <list>
#include <string>
#include <mutex>
#include "../game/GameClient.h"

class GameClient;

class Client {
public:
    Client(GameClient* gameClient);
    ~Client();

    //API
    //===============
    void setToSend(std::string message);
    std::string pollMessage();
    bool isThereAMessage();
    bool init();

private:
    std::string END_SERIALIZATION_SIMBOL = "x";
    char SEPARATOR = '_';

    int socketFD;
    std::mutex mu;
    bool clientOn;

    GameClient* gameClient = nullptr;

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
    void dispatchThread();

    //no podemos permitir que toquen esto desde afuera
    //===============
    int create();
    int connectToServer();
    int disconnectFromServer();

    void processIDFromTheServer(std::string msg);
    void processRenderableSerializedObject(std::string msg);
    const vector<string> split(const string& s, const char& c);
};


#endif //GAME_CLIENT_H
