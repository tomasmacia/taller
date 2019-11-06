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

    //for (int i = 0 ; i < DATA_REDUNDANCY ; i++){
     //   toSendMessagesQueue.push_back(message);
    //}
    //cout<<"SERVER-FROM MODEL: "<<message<<endl;
    cout<<"AMOUNT: "<<toSendMessagesQueue.size()<<endl;

    if (toSendMessagesQueue.size() > QUEUE_AMOUNT_THRESHOLD){
        toSendMessagesQueue.clear();
    }
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

    vector<string> newMessages;
    while (connectionOn) {

        //cout<<"SERVER-READ"<<endl;

        incomingQueueMutex.lock();
        newMessages = server->receive(socketFD);

        for (auto message : newMessages) {
            incomingMessagesQueue.push_back(message);
            cout << "SERVER-READ: " << message << endl;
        }
        newMessages.clear();
        incomingQueueMutex.unlock();
    }
    cout<<"SERVER-READ-DONE"<<endl;
}

void UserConnection::sendThread() {

    while (connectionOn) {

        //cout<<"SERVER-SEND"<<endl;

        sendQueueMutex.lock();

        for (auto message : toSendMessagesQueue){

            server->send(message, socketFD);
            //cout << "SERVER-SEND: " << message << endl;
        }
        toSendMessagesQueue.clear();
        sendQueueMutex.unlock();
    }
    cout<<"SERVER-SEND-DONE"<<endl;
}

void UserConnection::dispatchThread() {

    while(connectionOn) {

        //cout<<"SERVER-DISPATCH"<<endl;

        incomingQueueMutex.lock();

        for (auto message: incomingMessagesQueue){

            messageParser.parse(message, objectSerializer.getSeparatorCharacter());

            if (objectSerializer.validLoginFromClientMessage(messageParser.getCurrent())
                ||
                objectSerializer.validSerializedInputMessage(messageParser.getCurrent())){

                cout<<"SERVER-DISPATCH: "<< message <<endl;

                MessageId header = messageParser.getHeader();

                if (header == USER_PASS){

                    processLoginFromTheClient();
                }
                if (header == INPUT){
                    processInput();
                }
            }
        }
        incomingMessagesQueue.clear();
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