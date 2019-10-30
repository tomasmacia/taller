//
// Created by Tomás Macía on 27/10/2019.
//

#include "UserConnection.h"
#include <iostream>
#include <thread>
#include <sys/socket.h>

UserConnection::UserConnection(int socket, int userId, Server *server) {
    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
    this->connectionIsOn = true;
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

        if (connectionOff()) {
            connectionLost();
            //server->userConectionLost(userId);  AL FINAL BORRAMOS TODAS LAS CONEXIONES EN EL DESTRUCTOR DE SERVER (MAS PROLIJO)
            mu.unlock();            //TODO, ojo aca
            break;
        }
        mu.unlock();
    }
}

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

void UserConnection::init() {
    std::thread read = std::thread(&UserConnection::readThread, this);
    std::thread send = std::thread(&UserConnection::sendThread, this);
    read.join();
    send.join();
}
