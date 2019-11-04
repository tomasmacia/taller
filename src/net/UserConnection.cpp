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
    sendQueueMutex.unlock();
}

void UserConnection::start() {

    std::thread read(&UserConnection::readThread,this);
    std::thread send(&UserConnection::sendThread,this);
    std::thread dispatch(&UserConnection::dispatchThread,this);

    checkConnection();
    cout<<"checkConnection();"<<endl;
    read.join();
    cout<<"read.join();"<<endl;
    send.join();
    cout<<"send.join();"<<endl;
    dispatch.join();
    cout<<"dispatch.join();"<<endl;

    kill();
    cout<<"kill"<<endl;
}

void UserConnection::shutdown() {
    connectionOn = false;
}

//THREADS
//=========================================================================================
void UserConnection::readThread() {

    string incomingMessage;

    while(connectionOn) {

        incomingQueueMutex.lock();
        //cout<<"SERVER-READ"<<endl;
        /*
        incomingMessage = server->receive(socketFD);
        if (incomingMessage == objectSerializer.getFailure()){ continue;}
        if (incomingMessage == objectSerializer.getPingCode()){ continue;}
        else{

            incomingMessagesQueue.push_back(incomingMessage);
            cout<<"SERVER-READ: "<<incomingMessage<<endl;
        }*/
        incomingQueueMutex.unlock();
    }
    cout<<"readThread"<<endl;
}

void UserConnection::sendThread() {

    string toSendMessage;

    while (connectionOn) {

        sendQueueMutex.lock();
        //cout<<"SERVER-SEND"<<endl;

        /*
        cout << "THREAD: vacio :" << (toSendMessagesQueue.size() != 0) << endl;
        cout << "THREAD: amount to send: " << toSendMessagesQueue.size() << endl;
        cout << "THREAD: connections: " << server->numberOfConectionsEstablished() << endl;
        cout << "THREAD: ==================================" << endl;
        cout << endl;


        if (toSendMessagesQueue.size() != 0) {
            toSendMessage = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            server->send(toSendMessage, socketFD);
            //cout << "SERVER-SEND: " << toSendMessage << endl;
        }
        //cout<<"SERVER: cantidad de paquetes: "<<toSendMessagesQueue.size()<<endl;*/
        sendQueueMutex.unlock();
    }
    cout<<"sendThread"<<endl;
}

void UserConnection::dispatchThread() {

    string incomingMessage;

    while(connectionOn) {
        incomingQueueMutex.lock();
        //cout<<"SERVER-DISPATCH"<<endl;
        /*
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

            cout<<"SERVER-DISPATCH: "<<incomingMessage<<endl;
        }*/
        incomingQueueMutex.unlock();
    }
    cout<<"dispatchThread"<<endl;
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

    //aca pongo connectionOn en el while porque me podrian poner
    //connectionOn = false desde el server

    while (connectionOn && !connectionOff()){
        continue;
    }
    connectionOn = false;
}

bool UserConnection::connectionOff(){

    int n = server->send(objectSerializer.getPingCode(),socketFD);
    if (n < 0){
        return true;
    }
    return false;
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
}