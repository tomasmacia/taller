//
// Created by Tomás Macía on 27/10/2019.
//

#include "UserConnection.h"
#include <iostream>
#include <thread>

UserConnection::UserConnection(int socket, int userId, Server *server) {
    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
    this->connectionIsOn = true;
    init();
}

void UserConnection::setToSendMessage(std::string message){
    mu.lock();
    toSendMessagesQueue.push_back(message);
    mu.unlock();
}

void UserConnection::readThread() {
    while(connectionIsOn) {
        mu.lock();
        incomingMessage = server->receive(socketFD);
        incomingMessagesQueue.push_back(incomingMessage);
        mu.unlock();
    }
}

void UserConnection::sendThread() {
    while(connectionIsOn) {
        mu.lock();
        toSendMessage = toSendMessagesQueue.front();
        toSendMessagesQueue.pop_front();
        server->send(toSendMessage,socketFD);
        mu.unlock();
    }
}

void UserConnection::dispatchThread() {
    while(connectionIsOn) {
        incomingMessage = server->receive(socketFD);
        if (incomingMessage != CONTROL__ID_ON){
            connectionLost();
        }
    }
}

void UserConnection::connectionLost(){
    connectionIsOn = false;
}

void UserConnection::init() {
    std::thread read = std::thread(&UserConnection::readThread, this);
    std::thread send = std::thread(&UserConnection::sendThread, this);
    std::thread dispatch = std::thread(&UserConnection::dispatchThread, this);
    read.join();
    send.join();
    dispatch.join();
}
