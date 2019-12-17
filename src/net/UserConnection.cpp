//
// Created by Tomás Macía on 27/10/2019.
//

#include <unistd.h>
#include <sys/socket.h>
#include "UserConnection.h"
#include <iostream>



//API
//=========================================================================================
void UserConnection::setToSendMessage(std::string message){
    sendQueueMutex.lock();
    toSendMessagesQueue.push_back(message);
    sendQueueMutex.unlock();
}

void UserConnection::directSend(string message){
    server->send(message,socketFD);
}

void UserConnection::start() {

    std::thread read(&UserConnection::readThread,this);
    std::thread send(&UserConnection::sendThread,this);
    std::thread dispatch(&UserConnection::dispatchThread,this);

    checkConnection();

    read.join();
    send.join();
    dispatch.join();

    kill();
}

void UserConnection::shutdown() {
    setConnectionOff();
    ::close(socketFD);
    ::shutdown(socketFD, SHUT_WR);
}

bool UserConnection::hasPassedLogin(){
    return gameServer->isIDLogged(userId);
}

//THREADS
//=========================================================================================
void UserConnection::readThread() {

    string incomingMessage;
    while(isConnected()) {
        incomingMessage = server->receive(socketFD);
        //cout<<"SERVER-READ"<<endl;
        if (incomingMessage == objectSerializer.getFailure()){ continue;}
        if (incomingMessage == objectSerializer.getPingCode()){ continue;}
        else{
            incomingQueueMutex.lock();
            incomingMessagesQueue.push_back(incomingMessage);
            //cout<<"SERVER-READ: "<<incomingMessage<<endl;
            incomingQueueMutex.unlock();
        }
    }
}

void UserConnection::sendThread() {

    while (isConnected()) {

        sendQueueMutex.lock();
        std::string message;
        //cout<<"SERVER-SEND-mutex"<<endl;
        if (toSendMessagesQueue.size() != 0) {
            message = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            //cout << "SEND QUEUE POP" << endl;

            if (!message.empty()) {
                int n = server->send(message, socketFD);
                packageSent += 1;
                //cout << "SERVER-SEND: " << message << endl;
            }
        }
        sendQueueMutex.unlock();
    }
}

void UserConnection::dispatchThread() {

    while(isConnected()) {
        incomingQueueMutex.lock();
        if (!incomingMessagesQueue.empty()){

            string message = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();

            messageParser.parse(message, objectSerializer.getSeparatorCharacter());

            if (objectSerializer.validLoginFromClientMessage(messageParser.getCurrent())){
                processLoginFromTheClient();
            }

            else if (objectSerializer.validSerializedInputMessage(messageParser.getCurrent())){
                processInput();
            }
            //cout<<"SERVER-DISPATCH: "<< message <<endl;
        }
        incomingQueueMutex.unlock();
    }
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void UserConnection::processLoginFromTheClient() {

    if (objectSerializer.validLoginFromClientMessage(messageParser.getCurrent())){

        string user = objectSerializer.getUserFrom(messageParser.getCurrent());
        string pass = objectSerializer.getPassFrom(messageParser.getCurrent());
        gameServer->handleLogin(user, pass, userId);
    }
    else{
        string toSendMessage = objectSerializer.getInvalidCredentialMessage();
        server->setToSendToSpecific(toSendMessage,userId);
    }
}

void UserConnection::processInput() {//TODO HEAVY IN PERFORMANCE

    if (objectSerializer.validSerializedInputMessage(messageParser.getCurrent())){

        auto input = objectSerializer.reconstructInput(messageParser.getCurrent());
        gameServer->reciveNewInput(input);
    }
}

//DISCONECTION RELATED
//=========================================================================================

void UserConnection::checkConnection(){

    while (!connectionOff()){
        usleep(100000);
    }
    setConnectionOff();
    LogManager::logError("[SERVER]: conexion con " + to_string(userId) + " perdida");
}

bool UserConnection::isConnected() {
    bool isConnected;

    isConnectedMutex.lock();
    isConnected = connectionOn;
    isConnectedMutex.unlock();

    return isConnected;
}

void UserConnection::setConnectionOff() {
    isConnectedMutex.lock();
    connectionOn = false;
    isConnectedMutex.unlock();
}

bool UserConnection::connectionOff(){

    if (!isConnected()){
        return true;
    } else {
        return server->send(objectSerializer.getPingMessage(), socketFD) < 0;
    }
}

void UserConnection::kill(){
    server->removeConnection(userId);
}

//CONSTRUCTOR
//=========================================================================================
UserConnection::UserConnection(int socket, int userId, Server *server,GameServer* gameServer) {

    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
    this->gameServer = gameServer;
    this->packageCount = 0;
    this->packageSent = 0;
}