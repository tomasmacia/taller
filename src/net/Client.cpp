
#include <list>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <CLIArgumentParser.h>

#include "../LogLib/LogManager.h"
#include "../game/MessageId.h"
#include "../game/ToClientPack.h"
#include "Client.h"

#include <iostream>

using namespace std;

#define MAX_BYTES_BUFFER 128


#if __APPLE__
#define MSG_NOSIGNAL 0x2000 /* don't raise SIGPIPE */
#endif	// __APPLE__



//API
//=========================================================================================
void Client::notifyGameStoppedRunning(){
    //cout<<"entre"<<endl;
    //std::lock_guard<std::mutex> guard(mu);
    //cout<<"entre entre"<<endl;
    connectionOn = false;
}

bool Client::hasAchievedConnectionAttempt() {
    return connectionAttemptMade;
}

void Client::sendCredentials(string user, string pass){
    setToSend(objectSerializer.serializeCredentials(user,pass));
}

void Client::setToSend(std::string message){
    //sendQueueMutex.lock();
    toSendMessagesQueue.push_back(message);
    //sendQueueMutex.unlock();
}

bool Client::start(){

    create();
    connectToServer();
    gameClient->notifyAboutClientConectionToServerAttemptDone();

    std::thread read(&Client::readThread,this);
    std::thread send(&Client::sendThread,this);
    std::thread dispatch(&Client::dispatchThread,this);

    checkConnection();
    cout<<"termine check"<<endl;
    read.join();
    send.join();
    dispatch.join();
}

//THREADS
//=========================================================================================
void Client::readThread() {

    vector<string> newMessages;
    while (connectionOn) {

        //cout<<"CLIENT-READ"<<endl;
        newMessages = receive();
        //incomingQueueMutex.lock();
        for (auto message : newMessages) {
            incomingMessagesQueue.push_back(message);
        }
        //incomingQueueMutex.unlock();
        //cout << "CLIENT-READ: " << incomingMessage << endl;
        }
    cout<<"CLIENT-READ-DONE"<<endl;
}

void Client::sendThread() {

    while(connectionOn) {
        std::string message;
        //sendQueueMutex.lock();
        //cout<<"CLIENT-SEND"<<endl;

        if (!toSendMessagesQueue.empty()) {
            message = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
        }
        //sendQueueMutex.unlock();

        if (!message.empty()) {
            toSendMessage = message;
            send(toSendMessage);
            cout << "CLIENT-SEND: " << toSendMessage << endl;
        }
    }
    cout<<"CLIENT-SEND-DONE"<<endl;
}

void Client::dispatchThread() {
    while(connectionOn) {
        std::string message;
        //incomingQueueMutex.lock();
        //cout<<"CLIENT-DISPATCH"<<endl;

        if (!incomingMessagesQueue.empty()){
            message = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();
        }
        //incomingQueueMutex.unlock();

        if (!incomingMessage.empty()) {
            messageParser.parse(incomingMessage, objectSerializer.getSeparatorCharacter());
            MessageId header = messageParser.getHeader();

            if ((header == SUCCESS) || (header == INVALID_CREDENTIAL)
                ||
                (header == ALREADY_LOGGED_IN_CREDENTIAL) || (header == SERVER_FULL)){

                processResponseFromServer();
            }
            if (header == RENDERABLE){
                processRenderableSerializedObject();
            }

            cout<<"CLIENT-DISPATCH: "<< incomingMessage <<endl;
        }
    }
    cout<<"CLIENT-DISPATCH-DONE"<<endl;
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void Client::processResponseFromServer() {

    int id = objectSerializer.getIDFrom(messageParser.getCurrent());

    gameClient->setServerAknowledgeToLogin(messageParser.getHeader());

    if (messageParser.getHeader() == SUCCESS){
        gameClient->setPlayerId(id);
    }
}

void Client::processRenderableSerializedObject() {//TODO HEAVY IN PERFORMANCE
    gameClient->reciveRenderable(objectSerializer.reconstructRenderable(messageParser.getCurrent()));
}

//ACTUAL DATA TRANSFER
//=========================================================================================
int  Client::send(std::string msg) {

    char buff[MAX_BYTES_BUFFER]{0};
    strncpy(buff, msg.c_str(), sizeof(buff));
    buff[sizeof(buff) - 1] = 0;

    //int len = msg.size();
    //char bufferSend[len];//este buffer tiene que que ser otro distinto al de atributo

    return ::send(socketFD, buff, strlen(buff), MSG_NOSIGNAL);
}

vector<string> Client::receive() {

    //INIT
    //=================================
    char buff[MAX_BYTES_BUFFER];
    size_t size = MAX_BYTES_BUFFER;
    //=================================

    recv(socketFD, buff, size, 0);
    //cout <<"leido: "<< buff << endl;

    vector<string> m = messageParser.extractMeaningfulMessagesFromStream(buff,objectSerializer);
    //cout << "cantidad completos: "<<m.size()<<endl;
    //for (auto a: m){
        //cout<<"resultado: "<<a<<endl;
    //}
    //cout<<"========================="<<endl;
    //cout<<endl;
    return m;
}


//DISCONECTION RELATED
//=========================================================================================
void Client::checkConnection(){

    while (!connectionOff()){
        continue;
    }
    connectionOn = false;
}

bool Client::connectionOff(){

    std::lock_guard<std::mutex> guard(mu);

    if (!connectionOn){
        cout<<"mala conexion"<<endl;
        return true;
    }
    else {
        if (send(objectSerializer.getPingCode()) < 0) {
            cout << "mala conexion" << endl;
            return true;
        }
        else {
            return false;
        }
    }
}

int Client::disconnectFromServer() {
    close(socketFD);
    return 0;
}

//ERROR
//=========================================================================================
void Client::error(const char *msg) {
    LogManager::logError(msg);

}

//INIT & CONSTRUCTOR
//=========================================================================================
Client::Client(GameClient* gameClient) {
    maxBytesBuffer = MAX_BYTES_BUFFER;
    //char buf[MAX_BYTES_BUFFER];
    //buffer = buf;
    this->gameClient = gameClient;
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
        gameClient->end();
    }

    connectionAttemptMade = true;

    return socketFD;
}

//DESTROY
//=========================================================================================
Client::~Client() {
    disconnectFromServer();
}