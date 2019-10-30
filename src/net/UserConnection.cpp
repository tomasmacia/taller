//
// Created by Tomás Macía on 27/10/2019.
//

#include "UserConnection.h"
#include <iostream>
#include <thread>
#include <sys/socket.h>

UserConnection::UserConnection(int socket, int userId, Server *server,GameServer* gameServer) {
    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
    this->connectionIsOn = true;
    this->gameServer = gameServer;
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
        if (!toSendMessagesQueue.empty()){
            toSendMessage = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            server->send(toSendMessage,socketFD);
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

            std::string header = incomingMessage.substr(0,1);
            if (header == "0"){
                processLoginFromTheClient(incomingMessage);
            }
            if (header == "1"){
                processInput(incomingMessage);
            }
        }
        mu.unlock();
    }
}

void UserConnection::processLoginFromTheClient(std::string loginMsg) {

    vector<string> splited{split(loginMsg, SEPARATOR)};

    if (splited.size() != 4){//header,user,pass,endcaracter
        toSendMessage = "0_-1_" + END_SERIALIZATION_SIMBOL;
    }
    else{
        std::string user = splited.at(1);
        std::string pass = splited.at(2);
        toSendMessage = gameServer->validateLogin(user,pass,userId);
    }
    server->setToSendToSpecific(toSendMessage,userId);
}

void UserConnection::processInput(std::string inputMsg) {

    vector<string> splited{split(inputMsg, SEPARATOR)};

    if (splited.size() == 4){//header,action,id,endcaracter
        std::string action = splited.at(1);
        std::string id = splited.at(2);
        gameServer->reconstructInput(action,id);
        gameServer->addNewIDToGame(std::stoi(id));
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
    std::thread dispatch = std::thread(&UserConnection::dispatchThread, this);
    dispatch.join();
    read.join();
    send.join();
}

const vector<string> UserConnection::split(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

