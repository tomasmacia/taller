//
// Created by Tomás Macía on 27/10/2019.
//

#include <unistd.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "UserConnection.h"
#include <iostream>
#include <sys/socket.h>

#include "../game/MessageId.h"

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
    connectionOn = false;
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
    cout<<"SERVER-READ-DONE"<<endl;
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
                cout << "SERVER-SENT " << n << " bytes" << endl;
                cout << "SERVER-SEND: " << message << endl;
                cout<<endl;
                cout<<endl;
                cout<<endl;
            }
        }
        sendQueueMutex.unlock();
    }
    cout<<"SERVER-SEND-DONE"<<endl;
}

void UserConnection::dispatchThread() {

    while(connectionOn) {
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
    cout<<"SERVER-DISPATCH-DONE"<<endl;
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void UserConnection::processLoginFromTheClient() {

    string toSendMessage;

    if (objectSerializer.validLoginFromClientMessage(messageParser.getCurrent())){

        string user = objectSerializer.getUserFrom(messageParser.getCurrent());
        string pass = objectSerializer.getPassFrom(messageParser.getCurrent());
        toSendMessage = gameServer->validateLogin(user,pass,userId);
    }
    else{
        toSendMessage = objectSerializer.getInvalidCredentialMessage();
    }
    server->setToSendToSpecific(toSendMessage,userId);
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

    while (true){
        continue;
    }
    setConnectionOff();
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
        cout<<"mala conexion"<<endl;
        return true;
    } else {
        if (server->send(objectSerializer.getPingCode(),socketFD) < 0) {
            cout << "mala conexion" << endl;
            return true;
        } else {
            return false;
        }
    }
}

void UserConnection::kill(){
    server->removeConnection(userId);
}

//CONSTRUCTOR
//=========================================================================================
UserConnection::UserConnection(int socket, int userId, Server *server,GameServer* gameServer) {

    //incomingMessagesQueue = new list<string>();
    //toSendMessagesQueue = new list<string>();

    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
    this->gameServer = gameServer;
    this->packageCount = 0;
    this->packageSent = 0;
}