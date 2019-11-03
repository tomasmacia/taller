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
    //mu.lock();
    toSendMessagesQueue.push_back(message);
    //mu.unlock();
}

void UserConnection::init() {

    //std::thread read(&UserConnection::readThread,this);
    //read.detach();
    //std::thread send(&UserConnection::sendThread,this);
    //send.detach();
    //std::thread dispatch(&UserConnection::dispatchThread,this);
    //dispatch.detach();
}

//THREADS
//=========================================================================================
void UserConnection::readThread() {

    while(!connectionOff()) {
        mu.lock();
        incomingMessage = server->receive(socketFD);

        if (incomingMessage != objectSerializer.getPingCode()){

            //incomingMessagesQueue.push_back(incomingMessage);
            cout<<"SERVER-READ: "<<incomingMessage<<endl;
        }
        mu.unlock();
    }
    kill();
}

void UserConnection::sendThread() {

    while (!connectionOff()) {
        mu.lock();
        /*
        cout << "THREAD: vacio :" << (toSendMessagesQueue.size() != 0) << endl;
        cout << "THREAD: amount to send: " << toSendMessagesQueue.size() << endl;
        cout << "THREAD: connections: " << server->numberOfConectionsEstablished() << endl;
        cout << "THREAD: ==================================" << endl;
        cout << endl;*/

        if (toSendMessagesQueue.size() != 0) {
            toSendMessage = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            server->send(toSendMessage, socketFD);
            cout << "SERVER-SEND: " << toSendMessage << endl;
        }
        mu.unlock();
    }
    kill();
}

void UserConnection::dispatchThread() {

    while(!connectionOff()) {
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

            cout<<"SERVER-DISPATCH: "<<incomingMessage<<endl;
        }
        mu.unlock();
    }
    kill();
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

    int n = server->send(objectSerializer.getPingCode(),socketFD);
    if (n < 0){
        //cout<<"CONEXION MALA"<<endl;
        return true;
    }
    //cout<<"CONEXION BUENA"<<endl;
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

