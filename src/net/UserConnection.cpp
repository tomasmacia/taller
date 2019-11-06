//
// Created by Tomás Macía on 27/10/2019.
//

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
//    cout<<"AMOUNT: "<<toSendMessagesQueue.size()<<endl;
    //cout<< "Push message: " << message << endl;
    packageCount += 1;
    sendQueueMutex.unlock();
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
                cout<<endl;
            }
        }
        sendQueueMutex.unlock();


    }
    cout<<"SERVER-SEND-DONE"<<endl;
}

void UserConnection::dispatchThread() {


    while(isConnected()) {
        incomingQueueMutex.lock();
        string incomingMessage;
        //cout<<"SERVER-DISPATCH"<<endl;

        if (!incomingMessagesQueue.empty()){
            incomingMessage = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();
        }
        incomingQueueMutex.unlock();

        if (!incomingMessage.empty()) {
            messageParser.parse(incomingMessage, objectSerializer.getSeparatorCharacter());
            MessageId header = messageParser.getHeader();
            if (header == USER_PASS){
                processLoginFromTheClient(incomingMessage);
            }
            if (header == INPUT){
                processInput(incomingMessage);
            }

            //cout<<"SERVER-DISPATCH: "<< incomingMessage <<endl;
        }
    }
    cout<<"SERVER-DISPATCH-DONE"<<endl;
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void UserConnection::processLoginFromTheClient(std::string loginMsg) {

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

void UserConnection::processInput(std::string inputMsg) {//TODO HEAVY IN PERFORMANCE

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