//
// Created by Tomás Macía on 27/10/2019.
//

#include "UserConnection.h"
#include <iostream>
#include <thread>
#include <sys/socket.h>
#include "../LogLib/LogManager.h"

#include "../game/MessageId.h"

#include <iostream>


//API
//=========================================================================================
void UserConnection::setToSendMessage(std::string message){
    mu.lock();
    toSendMessagesQueue.push_back(message);
    mu.unlock();
}

void UserConnection::init() {
    //std::thread read = std::thread(&UserConnection::readThread, this);
    //read.detach();
    std::thread send = std::thread(&UserConnection::sendThread, this);
    send.detach();
    //std::thread dispatch = std::thread(&UserConnection::dispatchThread, this);
    //dispatch.detach();
}

//THREADS
//=========================================================================================
void UserConnection::readThread() {

    while(connectionIsOn) {
        mu.lock();
        incomingMessage = server->receive(socketFD);
        incomingMessagesQueue.push_back(incomingMessage);
        //LogManager::logDebug("SERVER-READ: " + incomingMessage);
        cout<<"SERVER-READ: "<<incomingMessage<<endl;
        mu.unlock();
    }
}

void UserConnection::sendThread() {
    while(connectionIsOn) {
        mu.lock();
        if (!toSendMessagesQueue.empty()){
            toSendMessage = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            server->send(toSendMessage,socketFD);
            //LogManager::logDebug("SERVER-SEND: " + toSendMessage);
            cout<<"SERVER-SEND: "<<toSendMessage<<endl;

            if (connectionOff()) {
                connectionLost();
                //server->userConectionLost(userId);  AL FINAL BORRAMOS TODAS LAS CONEXIONES EN EL DESTRUCTOR DE SERVER (MAS PROLIJO)
                mu.unlock();            //TODO, ojo aca
                break;
            }
        }
        mu.unlock();
    }
}

void UserConnection::dispatchThread() {
    while(connectionIsOn) {
        mu.lock();
        if (!incomingMessagesQueue.empty()){
            incomingMessage = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();

            messageParser.parse(incomingMessage, objectSerializer.getSeparatorCharacter());
            MessageId header = messageParser.getHeader();
            if (header == USER_PASS){
                processLoginFromTheClient(incomingMessage);
            }
            if (header == INPUT){
                processInput(incomingMessage);
            }
            //LogManager::logDebug("SERVER-DISPATCH: " + incomingMessage);
            cout<<"SERVER-DISPATCH: "<<incomingMessage<<endl;
        }
        mu.unlock();
    }
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void UserConnection::processLoginFromTheClient(std::string loginMsg) {

    vector<string> currentParsedMessage = messageParser.getCurrent();

    if (objectSerializer.validLoginFromClientMessage(currentParsedMessage)){

        string user = objectSerializer.getUserFrom(currentParsedMessage);
        string pass = objectSerializer.getPassFrom(currentParsedMessage);
        toSendMessage = gameServer->validateLogin(user,pass,userId);
    }
    else{
        toSendMessage = objectSerializer.getInvalidCredentialMessage();
    }
    server->setToSendToSpecific(toSendMessage,userId);
}

void UserConnection::processInput(std::string inputMsg) {

    vector<string> currentParsedMessage = messageParser.getCurrent();

    if (objectSerializer.validSerializedInputMessage(currentParsedMessage)){

        auto input = objectSerializer.reconstructInput(currentParsedMessage);
        gameServer->reciveNewInput(input);
    }
}

//DISCONECTION RELATED
//=========================================================================================
bool UserConnection::connectionOff(){
    int error_code;
    socklen_t error_code_size = sizeof(error_code);
    if (getsockopt(socketFD, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size) < 0){
        return true;
    }
    return false;
}

void UserConnection::connectionLost(){
    connectionIsOn = false;
}

//CONSTRUCTOR
//=========================================================================================
UserConnection::UserConnection(int socket, int userId, Server *server,GameServer* gameServer) {
    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
    this->connectionIsOn = true;
    this->gameServer = gameServer;
}

