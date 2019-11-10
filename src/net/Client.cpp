#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <CLIArgumentParser.h>

#include "../LogLib/LogManager.h"
#include "../game/MessageId.h"
#include "Client.h"

#include <iostream>

using namespace std;

#define MAX_BYTES_BUFFER 1500


#if __APPLE__
#define MSG_NOSIGNAL 0x2000 /* don't raise SIGPIPE */
#endif	// __APPLE__



//API
//=========================================================================================
void Client::notifyGameStoppedRunning(){
    connectionOn = false;
}

bool Client::hasAchievedConnectionAttempt() {
    return connectionAttemptMade;
}

void Client::sendCredentials(string user, string pass){
    setToSend(objectSerializer.serializeCredentials(user,pass));
}

void Client::setToSend(std::string message){
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
}

//THREADS
//=========================================================================================
void Client::readThread() {

    string newMessage;
    while (connectionOn) {
        newMessage = receive();
        incomingQueueMutex.lock();

        incomingMessagesQueue.push_back(newMessage);
        //cout<<endl;
        //cout<<"CLIENT-READ: "<<endl;
        //cout << "CLIENT-READ: " << newMessage << endl;
        incomingQueueMutex.unlock();
    }
}

void Client::sendThread() {

    while (connectionOn) {
        sendQueueMutex.lock();

        if (!toSendMessagesQueue.empty()){
            string message = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();

            send(message);
            cout<<endl;
            //cout<<"CLIENT-SEND: "<<endl;
            //cout << "CLIENT-SEND: " << message << endl;
        }
        sendQueueMutex.unlock();
    }
}

void Client::dispatchThread() {

    int totalDispatched = 0;
    int validRenderablesPackDispatched = 0;
    while(connectionOn) {
        incomingQueueMutex.lock();
        if (!incomingMessagesQueue.empty()){

            string message = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();
            totalDispatched++;

            if (objectSerializer.validSerializedSetOfObjectsMessage(messageParser.parse(message, objectSerializer.getObjectSeparator()))){
                processRenderableSerializedObject();
                validRenderablesPackDispatched++;
                //cout<<endl;
                //cout<<"CLIENT-DISPATCH: "<<validRenderablesPackDispatched<<endl;
                //cout<<"CLIENT-DISPATCH: "<<totalDispatched<<endl;
                //cout<<"CLIENT-DISPATCH: "<<(float)validRenderablesPackDispatched/(float)totalDispatched*100<<"%"<<endl;
                //cout<<"CLIENT-DISPATCH: "<< message <<endl;
            }

            else if (objectSerializer.validLoginFromServerMessage(messageParser.parse(message, objectSerializer.getSeparatorCharacter()))){
                processResponseFromServer();
                //cout<<endl;
                //cout<<"CLIENT-DISPATCH: "<< message <<endl;
            }
        }
        incomingQueueMutex.unlock();
    }
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
    gameClient->reciveRenderables(messageParser.getCurrent());
    //gameClient->render();
}

bool Client::alreadyLoggedIn() {
    return gameClient->alreadyLoggedIn();
}

//ACTUAL DATA TRANSFER
//=========================================================================================
int Client::send(std::string msg) {

    char buff[MAX_BYTES_BUFFER]{0};
    strncpy(buff, msg.c_str(), sizeof(buff));
    buff[sizeof(buff) - 1] = 0;

    //int len = msg.size();
    //char bufferSend[len];//este buffer tiene que que ser otro distinto al de atributo

    int bytesSent = 0;

    while (bytesSent < MAX_BYTES_BUFFER - 1) {
        int n = ::send(socketFD, buff, MAX_BYTES_BUFFER - 1, MSG_NOSIGNAL);
        //if (n < 0) {
           //error("ERROR sending");
        //}

        bytesSent += n;
    }

    return bytesSent;
}

std::string Client::receive() {

    char buff[MAX_BYTES_BUFFER]{0};
    //size_t size = MAX_BYTES_BUFFER;

    int bytesRead = 0;

    while (bytesRead < MAX_BYTES_BUFFER - 1) {
        int n = recv(socketFD, buff, MAX_BYTES_BUFFER - 1, 0);
        if (n < 0) {
            //error("ERROR sending");
            return objectSerializer.getFailure();
        }

        bytesRead += n;
    }

    char end = objectSerializer.getEndOfSerializationSymbol();
    char padding = objectSerializer.getPaddingSymbol();
    std::string parsed = messageParser.extractMeaningfulMessageFromStream(buff, end,padding);
    return parsed;
}


//DISCONECTION RELATED
//=========================================================================================
void Client::checkConnection(){

    while (!connectionOff()){
        usleep(100000);
   }
    connectionOn = false;
    LogManager::logError("[CLIENT]: conexion perdida");
}

bool Client::connectionOff(){

    if (!connectionOn){
        return true;
    }
    else {
        return send(objectSerializer.getPingCode()) < 0;
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
        cout<<"Connection to server failed"<<endl;
        gameClient->end();
    }
    LogManager::logInfo("[CLIENT]: Conexion establecida");
    connectionAttemptMade = true;

    return socketFD;
}

//DESTROY
//=========================================================================================
Client::~Client() {
    disconnectFromServer();
}