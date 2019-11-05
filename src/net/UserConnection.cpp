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
    cout<<"SERVER-FROM MODEL: "<<message<<endl;
    cout<<"AMOUNT: "<<toSendMessagesQueue.size()<<endl;
    if (toSendMessagesQueue.size() > QUEUE_AMOUNT_THRESHOLD){
        toSendMessagesQueue.clear();
    }
    sendQueueMutex.unlock();
}

void UserConnection::start() {

    //std::thread read(&UserConnection::readThread,this);
    std::thread send(&UserConnection::sendThread,this);
    //std::thread dispatch(&UserConnection::dispatchThread,this);

    checkConnection();

    //read.join();
    send.join();
    //dispatch.join();

    kill();
}

void UserConnection::shutdown() {
    connectionOn = false;
}

//THREADS
//=========================================================================================
void UserConnection::readThread() {

    vector<string> newMessages;
    while (connectionOn) {

        cout<<"SERVER-READ"<<endl;
        newMessages = server->receive(socketFD);
        //incomingQueueMutex.lock();
        for (auto message : newMessages) {
            incomingMessagesQueue.push_back(message);
        }
        incomingQueueMutex.unlock();
        //cout << "SERVER-READ: " << incomingMessage << endl;
    }
    cout<<"SERVER-READ-DONE"<<endl;
}

void UserConnection::sendThread() {

    while (connectionOn) {
        std::string message;

        cout<<"SERVER-SEND"<<endl;

        sendQueueMutex.lock();
        if (toSendMessagesQueue.size() != 0) {
            message = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();

        }
        sendQueueMutex.unlock();

        if (!message.empty()) {
            server->send(message, socketFD);
            cout << "SERVER-SEND: " << message << endl;
        }
    }
    cout<<"SERVER-SEND-DONE"<<endl;
}

void UserConnection::dispatchThread() {


    while(connectionOn) {
        string incomingMessage;
        incomingQueueMutex.lock();
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

            cout<<"SERVER-DISPATCH: "<< incomingMessage <<endl;
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

    while (!connectionOff()){
        continue;
    }
    connectionOn = false;
}

bool UserConnection::connectionOff(){

    if (!connectionOn){
        cout<<"mala conexion"<<endl;
        return true;
    }
    else {
        if (server->send(objectSerializer.getPingCode(),socketFD) < 0) {
            cout << "mala conexion" << endl;
            return true;
        }
        else {
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
}