#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <errno.h>
#include "../CLIAparser/CLIArgumentParser.h"

#include "../logger/LogManager.h"
#include "../enumerates/MessageId.h"
#include "Client.h"

#include <iostream>
#include <utility>

using namespace std;

#define MAX_BYTES_BUFFER 2500

#if __APPLE__
#define MSG_NOSIGNAL 0x2000 /* don't raise SIGPIPE */
#endif	// __APPLE__



//API
//=========================================================================================
void Client::notifyGameStoppedRunning(){
    setConnectionOff();
}

bool Client::hasAchievedConnectionAttempt() {
    return connectionAttemptMade;
}

void Client::sendCredentials(string user, string pass){
    setToSend(objectSerializer->serializeCredentials(std::move(user),std::move(pass)));
}

void Client::setToSend(const std::string& message){
    sendQueueMutex.lock();
    toSendMessagesQueue.push_back(message);
    sendQueueMutex.unlock();
}

bool Client::start(){

    create();
    connectToServer();
    gameClient->notifyAboutClientConectionToServerAttemptDone();

    std::thread read(&Client::readThread,this);
    std::thread send(&Client::sendThread,this);
    std::thread dispatch(&Client::dispatchThread,this);

    checkConnection();

    read.join();
    send.join();
    dispatch.join();

    //gameClient->disconnected();

    return true;
}


void Client::client_noBlock() {
    struct timeval tv{} ;
    tv.tv_usec =10000;
    tv.tv_sec = 1;

    setsockopt(socketFD,SOL_SOCKET,SO_SNDTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
    setsockopt(socketFD,SOL_SOCKET,SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
}

//THREADS
//=========================================================================================
void Client::readThread() {

    string incomingMessage;
    while(isConnected()) {
        incomingMessage = receive();
        //cout<<"CLIENT-READ"<<endl;
        if (incomingMessage == objectSerializer->getFailure()){ continue;}
        if (incomingMessage == objectSerializer->getPingCode()){ continue;}
        else{
            incomingQueueMutex.lock();
            incomingMessagesQueue.push_back(incomingMessage);
            //cout<<"CLIENT-READ: "<<incomingMessage<<endl;
            incomingQueueMutex.unlock();
        }
    }
}

void Client::sendThread() {

    while (isConnected()) {
        sendQueueMutex.lock();

        if (!toSendMessagesQueue.empty()){
            string message = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();

            send(message);
            //cout<<endl;
            //cout<<"CLIENT-SEND: "<<endl;
            //cout << "CLIENT-SEND: " << message << endl;
        }
        sendQueueMutex.unlock();
    }
}

void Client::dispatchThread() {

    while(isConnected()) {
        incomingQueueMutex.lock();
        if (!incomingMessagesQueue.empty()){

            string message = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();
            //totalDispatched++;

            if (objectSerializer->validSerializedSetOfObjectsMessage(messageParser.parse(message, objectSerializer->getObjectSeparator()))){
                processRenderableSerializedObject();
                //validRenderablesPackDispatched++;
                //cout<<endl;
                //cout<<"CLIENT-DISPATCH: "<<validRenderablesPackDispatched<<endl;
                //cout<<"CLIENT-DISPATCH: "<<totalDispatched<<endl;
                //cout<<"CLIENT-DISPATCH: "<<(float)validRenderablesPackDispatched/(float)totalDispatched*100<<"%"<<endl;
                //cout<<"CLIENT-DISPATCH: "<< message <<endl;
            }

            else if (objectSerializer->validLoginFromServerMessage(messageParser.parse(message, objectSerializer->getSeparatorCharacter()))){
                processResponseFromServer();
                //cout<<endl;
                //cout<<"CLIENT-DISPATCH: "<< message <<endl;
            }

            else if (objectSerializer->validEndOfGameMessage(messageParser.parse(message, objectSerializer->getSeparatorCharacter()))){
                processEndOfGame();
            }

            else if (objectSerializer->validPlayerDiedMessage(messageParser.parse(message, objectSerializer->getSeparatorCharacter()))){
                processPlayerDeath();
            }

            else if (objectSerializer->validGameStartedMessage(messageParser.parse(message, objectSerializer->getSeparatorCharacter()))){
                processGameStart();
            }
        }
        incomingQueueMutex.unlock();
    }
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void Client::processResponseFromServer() {

    int id = objectSerializer->getIDFrom(messageParser.getCurrent());

    gameClient->setServerAknowledgeToLogin(messageParser.getHeader());

    if (messageParser.getHeader() == SUCCESS){
        gameClient->setPlayerId(id);
        gameClient->setPlayerColor(messageParser.getCurrent()->at(messageParser.getCurrent()->size()-1));
    }
}

void Client::processRenderableSerializedObject() {//TODO HEAVY IN PERFORMANCE
    gameClient->reciveRenderables(messageParser.getCurrent());
}

void Client::processEndOfGame() {
    gameClient->notifyEndOfGame();
}

void Client::processPlayerDeath() {
    int id = std::stoi(messageParser.getCurrent()->at(2));
    gameClient->processPlayerDeath(id);
}

void Client::processGameStart() {
    gameClient->notifyGameStart();
}


//ACTUAL DATA TRANSFER
//=========================================================================================
int Client::send(const std::string& msg) {

    char buff[MAX_BYTES_BUFFER]{0};
    strncpy(buff, msg.c_str(), sizeof(buff));

    int n = 0;

    while (n != MAX_BYTES_BUFFER) {
        n = ::send(socketFD, buff, MAX_BYTES_BUFFER, MSG_NOSIGNAL);
        if (n <= 0){
            if (errno != EAGAIN){
                error("error sending | errno: " + to_string(errno));
                setConnectionOff();
            }
        }
    }
    return n;
}


std::string Client::receive() {

    char buff[MAX_BYTES_BUFFER]{0};
    int n = 0;

    while (n != MAX_BYTES_BUFFER) {
        n = recv(socketFD, buff, MAX_BYTES_BUFFER, 0);
        //cout << "CLIENT-READ: " << buff << endl;
        if (n <= 0){
            if (errno != EAGAIN){
                error("error reading | errno: " + to_string(errno));
                setConnectionOff();
            }
            return objectSerializer->getFailure();
        }
    }

    char end = objectSerializer->getEndOfSerializationSymbol();
    char padding = objectSerializer->getPaddingSymbol();
    char start = objectSerializer->getStartSerializationSymbol();
    string failureMessage = objectSerializer->getFailure();
    std::string parsed = messageParser.extractMeaningfulMessageFromStream(buff,MAX_BYTES_BUFFER, failureMessage, start, end,padding);
    //cout << "CLIENT-READ: " << parsed << endl;
    return parsed;
}

//DISCONECTION RELATED
//=========================================================================================
void Client::checkConnection(){

    while (!connectionOff()){
        usleep(100000);
   }
    setConnectionOff();
    LogManager::logInfo("[CLIENT]: conexion perdida");
}

bool Client::isConnected() {
    bool isConnected;

    connectionMutex.lock();
    isConnected = connectionOn;
    connectionMutex.unlock();

    return isConnected;
}

void Client::setConnectionOff() {
    connectionMutex.lock();
    if (gameClient->isOn()){    //es por la pantalla de desconexion
        gameClient->disconnected();
    }
    connectionOn = false;
    connectionMutex.unlock();
}

bool Client::connectionOff(){

    if (!connectionOn){
        return true;
    }
    else {
        return send(objectSerializer->getPingMessage()) < 0;
    }
}

int Client::disconnectFromServer() {
    close(socketFD);
    return 0;
}

//ERROR
//=========================================================================================
void Client::error(basic_string<char, char_traits<char>, allocator<char>> msg) {
    LogManager::logError("[CLIENT]: " + msg);
}

//INIT & CONSTRUCTOR
//=========================================================================================
Client::Client(GameClient* gameClient) {
    maxBytesBuffer = MAX_BYTES_BUFFER;
    this->gameClient = gameClient;
    this->objectSerializer = new ObjectSerializer(gameClient->getConfig());
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
        cout<<"Connection to server failed"<<endl;
        gameClient->end();
    }
    else{
        LogManager::logInfo("[CLIENT]: Conexion establecida");
        gameClient->connected();
        connectionOn = true;

        int flag = 1;
        //setsockopt(socketFD, SOL_SOCKET, SO_KEEPALIVE, (void *)&flag, sizeof(flag));
    }
    connectionAttemptMade = true;

    return socketFD;
}

//DESTROY
//=========================================================================================
Client::~Client() {
    disconnectFromServer();
}
