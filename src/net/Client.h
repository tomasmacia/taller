//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <list>
#include <string>
#include <mutex>
#include <thread>
#include "../game/MessageParser.h"
#include "../game/ObjectSerializer.h"
#include "../game/GameClient.h"

class GameClient;
class Client {
public:
    Client(GameClient* gameClient);
    ~Client();

    //API
    //===============================
    void setToSend(std::string message);
    bool start();

private:
    //THREADS
    //===============================
    void readThread();
    void sendThread();
    void dispatchThread();


    //ACTUAL DATA TRANSFER
    //===============================
    int send(std::string msg);
    string receive();

    //DISPATCHING OF INCOMMING MESSAGES
    //===============================
    void processResponseFromServer();
    void processRenderableSerializedObject();

    //DISCONECTION RELATED
    //===============================
    void checkConnection();
    bool connectionOff();
    int disconnectFromServer();

    //ERROR
    //===============================
    void error(const char* msg);

    //INIT
    //===============================
    int create();
    int connectToServer();

    //ATRIBUTES
    //===============================
    std::mutex sendQueueMutex;
    std::mutex incomingQueueMutex;
    int socketFD;
    int maxBytesBuffer;
    //char* buffer;

    bool connectionOn = true;

    MessageParser messageParser;
    ObjectSerializer objectSerializer;
    GameClient* gameClient = nullptr;

    string incomingMessage;
    string toSendMessage;
    list<string> toSendMessagesQueue;
    list<string> incomingMessagesQueue;
};

#endif //GAME_CLIENT_H
