
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <CLIArgumentParser.h>
#include <thread>
#include "../LogLib/LogManager.h"
#include "../game/MessageId.h"
#include "../game/ToClientPack.h"
#include "Client.h"

#include <iostream>

using namespace std;

#define MAX_BYTES_BUFFER 4096
#define MSG_NOSIGNAL 0


//API
//=========================================================================================
void Client::setToSend(std::string message){
    sendQueueMutex.lock();
    toSendMessagesQueue.push_back(message);
    sendQueueMutex.unlock();
}

//THREADS
//=========================================================================================
void Client::readThread() {

    while (!connectionOff()) {
        incomingMessage = receive();

        if (incomingMessage != objectSerializer.getPingCode()) {
            incomingQueueMutex.lock();
            incomingMessagesQueue.push_back(incomingMessage);
            cout << "CLIENT-READ: " << incomingMessage << endl;
            incomingQueueMutex.unlock();
        }
        disconnectFromServer();
    }
}

void Client::sendThread() {

    while(!connectionOff()) {
        sendQueueMutex.lock();
        if (!toSendMessagesQueue.empty()) {
            toSendMessage = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            send(toSendMessage);
            cout << "CLIENT-SEND: " << toSendMessage << endl;
        }
        sendQueueMutex.unlock();
    }
    disconnectFromServer();
}

void Client::dispatchThread() {
    while(!connectionOff()) {
        incomingQueueMutex.lock();
        if (!incomingMessagesQueue.empty()){
            incomingMessage = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();

            messageParser.parse(incomingMessage, objectSerializer.getSeparatorCharacter());
            MessageId header = messageParser.getHeader();
            if (header == SUCCESS                      || header == INVALID_CREDENTIAL ||
                header == ALREADY_LOGGED_IN_CREDENTIAL || header == SERVER_FULL){

                processResponseFromServer();
            }
            if (header == RENDERABLE){
                processRenderableSerializedObject();
            }
            //LogManager::logDebug("CLIENT-DISPATCH: " + incomingMessage);
            cout<<"CLIENT-DISPATCH: "<<incomingMessage<<endl;
        }
        incomingQueueMutex.unlock();
    }
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void Client::processResponseFromServer() {

    vector<string> currentParsedMessage = messageParser.getCurrent();

    if (objectSerializer.validLoginFromServerMessage(currentParsedMessage)){

        int id = objectSerializer.getIDFrom(currentParsedMessage);

        gameClient->setServerAknowledgeToLogin(messageParser.getHeader());

        if (messageParser.getHeader() == SUCCESS){
            gameClient->setPlayerId(id);
        }
    }
    else{
        gameClient->setServerAknowledgeToLogin(INVALID_CREDENTIAL);
    }
}

void Client::processRenderableSerializedObject() {

    vector<string> currentParsedMessage = messageParser.getCurrent();

    if (objectSerializer.validSerializedObjectMessage(currentParsedMessage)){

        ToClientPack renderable = objectSerializer.reconstructRenderable(currentParsedMessage);
        gameClient->reciveRenderable(renderable);
    }
}

//ACTUAL DATA TRANSFER
//=========================================================================================
int  Client::send(std::string msg) {

    char buff[MAX_BYTES_BUFFER]{0};

    strncpy(buff, msg.c_str(), sizeof(buff));
    buff[sizeof(buff) - 1] = 0;

    return ::send(socketFD, buff, strlen(buff), MSG_NOSIGNAL);
}

std::string Client::receive() {
    char buff[MAX_BYTES_BUFFER]{0};

    //strncpy(buff, msg.c_str(), sizeof(buff));
    //buff[sizeof(buff) - 1] = 0;

    int n = read(socketFD, buff, MAX_BYTES_BUFFER);

    char end = objectSerializer.getEndOfSerializationCharacterget();
    return messageParser.extractMeaningfulMessageFromStream(buff, end);
}


//DISCONECTION RELATED
//=========================================================================================
bool Client::connectionOff(){

    int n = send(objectSerializer.getPingCode());
    if (n < 0){
        return true;
    }
    return false;
}

int Client::disconnectFromServer() {
    close(socketFD);
    return 0;
}

//ERROR
//=========================================================================================
void Client::error(const char *msg) {
    //mu.lock();
    LogManager::logError(msg);
    //mu.unlock();
}

//INIT & CONSTRUCTOR
//=========================================================================================
Client::Client(GameClient* gameClient) {
    maxBytesBuffer = MAX_BYTES_BUFFER;
    //char buf[MAX_BYTES_BUFFER];
    //buffer = buf;
    this->gameClient = gameClient;
}

bool Client::init(){

    create();
    connectToServer();

    //std::thread read(&Client::readThread,this);
    //read.detach();
    std::thread send(&Client::sendThread,this);
    send.detach();
    //std::thread dispatch(&Client::dispatchThread,this);
    //dispatch.detach();
}

int Client::create() {
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        error("ERROR opening socket");
    }

    return socketFD;
}

int Client::connectToServer() {
    string strServerAddress = CLIArgumentParser::getInstance().getServerAddress();
    string strPort = CLIArgumentParser::getInstance().getServerPort();

    struct sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    inet_pton(AF_INET, strServerAddress.c_str(), &(serverAddress.sin_addr));
    serverAddress.sin_port = htons(stoi(strPort));

    if (connect(socketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        error("ERROR connecting");
        //socketFD = -1;
    }
    return socketFD;
}

//DESTROY
//=========================================================================================
Client::~Client() {
    disconnectFromServer();
}