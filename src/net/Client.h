//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include <list>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "messaging/MessageParser.h"
#include "messaging/ObjectSerializer.h"
#include "../game/GameClient.h"

class GameClient;
class Client {
public:
    Client(GameClient* gameClient);
    ~Client();

    //API
    //===============================
    void setToSend(const std::string& message);
    bool start();
    void sendCredentials(string user, string pass);
    bool hasAchievedConnectionAttempt();
    void notifyGameStoppedRunning();
    void client_noBlock();

private:
    //THREADS
    //===============================
    void readThread();
    void sendThread();
    void dispatchThread();


    //ACTUAL DATA TRANSFER
    //===============================
    int send(const std::string& msg);
    string receive();

    //DISPATCHING OF INCOMMING MESSAGES
    //===============================
    void processResponseFromServer();
    bool alreadyLoggedIn();
    void processRenderableSerializedObject();

    //DISCONECTION RELATED
    //===============================
    void checkConnection();
    bool isConnected();
    void setConnectionOff();
    bool connectionOff();
    int disconnectFromServer();

    //ERROR
    //===============================
    void error(basic_string<char, char_traits<char>, allocator<char>> msg);

    //INIT
    //===============================
    int create();
    int connectToServer();

    //ATRIBUTES
    //===============================
    std::mutex connectionMutex;
    std::mutex sendQueueMutex;
    std::mutex incomingQueueMutex;
    int socketFD{};
    int maxBytesBuffer;
    //char* buffer;

    const double TIMEOUT = 1;
    time_t lastServerPingTime;
    bool serverAlive = true;
    bool connectionOn = false;
    bool connectionAttemptMade = false;

    MessageParser messageParser;
    ObjectSerializer *objectSerializer = nullptr;
    GameClient* gameClient = nullptr;

    list<string> toSendMessagesQueue;
    list<string> incomingMessagesQueue;

    void processEndOfGame();

    void processPlayerDeath();

    void processGameStart();

    void setDisconnected();
};

#endif //GAME_CLIENT_H
