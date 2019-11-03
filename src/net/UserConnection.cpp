//
// Created by Tomás Macía on 27/10/2019.
//

#include "UserConnection.h"
#include <iostream>
#include <thread>
#include <sys/socket.h>

#include "../game/MessageId.h"


//API
//=========================================================================================
void UserConnection::setToSendMessage(std::string message){
    mutexSend.lock();
    toSendMessagesQueue.push_back(message);
    mutexSend.unlock();
}

void UserConnection::init() {
    std::thread read = std::thread(&UserConnection::readThread, this);
    std::thread send = std::thread(&UserConnection::sendThread, this);
    std::thread dispatch = std::thread(&UserConnection::dispatchThread, this);
    read.detach();
    send.join();
    dispatch.join();
}

//THREADS
//=========================================================================================
void UserConnection::readThread() {
    while(connectionIsOn) {
        incomingMessage = server->receive(socketFD);
        if (!incomingMessage.empty()) {

            mutexReceive.lock();
            printf("[SERVER-read]: UserID %d sent %s\n", userId, incomingMessage.c_str());// + to_string(userId) + " sent " + incomingMessage);// << std::endl;
            incomingMessagesQueue.push_back(incomingMessage);
            mutexReceive.unlock();
        }
    }
}

//void UserConnection::sendThread() {
//    while(connectionIsOn) {
//        mutexSend.lock();
//        if (!toSendMessagesQueue.empty()){
//            toSendMessage = toSendMessagesQueue.front();
//            toSendMessagesQueue.pop_front();
//            server->send(toSendMessage,socketFD);
//            std::cout << "[SERVER-send]: UserID " << userId << " will receive " << toSendMessage << std::endl;
//            if (connectionOff()) {
//                connectionLost();
//                //server->userConectionLost(userId);  AL FINAL BORRAMOS TODAS LAS CONEXIONES EN EL DESTRUCTOR DE SERVER (MAS PROLIJO)
//                //mutexSend.unlock();            //TODO, ojo aca
//                break;
//            }
//        }
//        //mutexSend.unlock();
//    }
//}

void UserConnection::sendThread() {
    while(connectionIsOn) {
        std::string message;

        mutexSend.lock();
        if (!toSendMessagesQueue.empty()){
            message = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            if (connectionOff()) {
                connectionLost();
                //server->userConectionLost(userId);  AL FINAL BORRAMOS TODAS LAS CONEXIONES EN EL DESTRUCTOR DE SERVER (MAS PROLIJO)
                mutexSend.unlock();            //TODO, ojo aca
                break;
            }
        }
        mutexSend.unlock();

        if (!message.empty()) {
            server->send(message,socketFD);
            std::cout << "[SERVER-send]: UserID " << userId << " will receive " << message << std::endl;
        }
    }
}

void UserConnection::dispatchThread() {
    while(connectionIsOn) {
        mutexReceive.lock();
        std::string message;

        if (!incomingMessagesQueue.empty()) {
            message = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();
        }

        if (!message.empty()) {
            messageParser.parse(incomingMessage, objectSerializer.getSeparatorCharacter());
            MessageId header = messageParser.getHeader();
            if (header == USER_PASS){
                processLoginFromTheClient(incomingMessage);
            }
            if (header == INPUT){
                processInput(incomingMessage);
            }
        }
        mutexReceive.unlock();

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

