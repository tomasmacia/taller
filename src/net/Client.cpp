
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <CLIArgumentParser.h>
#include <thread>
#include "../LogLib/LogManager.h"
#include "../game/Header.h"
#include "../game/ToClientPack.h"
#include "Client.h"

using namespace std;

#define MAX_BYTES_BUFFER 4096


//API
//=========================================================================================
void Client::setToSend(std::string message){
    mu.lock();
    toSendMessagesQueue.push_back(message);
    mu.unlock();
}

//THREADS
//=========================================================================================
void Client::readThread() {
    while(clientOn) {
        mu.lock();
        incomingMessage = receive();
        incomingMessagesQueue.push_back(incomingMessage);
        mu.unlock();
    }
}

void Client::sendThread() {
    while(clientOn) {
        mu.lock();
        if (!toSendMessagesQueue.empty()){
            toSendMessage = toSendMessagesQueue.front();
            toSendMessagesQueue.pop_front();
            send(toSendMessage);

            if (connectionOff()) {
                disconnectFromServer();
                mu.unlock();            //TODO, ojo aca
                break;
            }
        }
        mu.unlock();
    }
}

void Client::dispatchThread() {
    while(clientOn) {
        mu.lock();
        if (!incomingMessagesQueue.empty()){
            incomingMessage = incomingMessagesQueue.front();
            incomingMessagesQueue.pop_front();

            messageParser.parse(incomingMessage, objectSerializer.getSeparatorCharacter());
            Header header = messageParser.getHeader();
            if (header == LOGIN){
                processIDFromServer();
            }
            if (header == GAME){
                processRenderableSerializedObject();
            }
        }
        mu.unlock();
    }
}

//DISPATCHING INCOMING MESSAGES
//=========================================================================================
void Client::processIDFromServer() {

    vector<string> currentParsedMessage = messageParser.getCurrent();

    if (objectSerializer.validLoginIDFromServerMessage(currentParsedMessage)){

        int id = objectSerializer.getIDFrom(currentParsedMessage);

        gameClient->sendAknowledgeToLogerMenu(id);
        gameClient->setPlayerId(id);
    }
    else{
        gameClient->sendAknowledgeToLogerMenu(objectSerializer.getFailureAcknowledgeSignal());
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
int Client::send(std::string msg) {

    int len = msg.size() + 1;
    char bufferSend[len];//este buffer tiene que que ser otro distinto al de atributo
    strcpy(bufferSend, msg.c_str());

    int n = write(socketFD, bufferSend, strlen(buffer));
    if (n < 0) {
        error("ERROR writing to socket");
    }
    return socketFD;
}

std::string Client::receive() {
    int n = read(socketFD, buffer, MAX_BYTES_BUFFER);
    if (n < 0) {
        error("ERROR reading from socket");
    }
    return messageParser.extractMeaningfulMessageFromStream(buffer,
                                                objectSerializer.getSeparatorCharacter(),
                                                objectSerializer.getEndOfSerializationCharacterget());
}

//DISCONECTION RELATED
//=========================================================================================
bool Client::connectionOff(){
    int error_code;
    socklen_t error_code_size = sizeof(error_code);
    if (getsockopt(socketFD, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size) < 0){
        clientOn = false;
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
    mu.lock();
    LogManager::logError(msg);
    clientOn = false;
    mu.unlock();
}

//INIT & CONSTRUCTOR
//=========================================================================================
Client::Client(GameClient* gameClient) {
    clientOn = true;
    maxBytesBuffer = MAX_BYTES_BUFFER;
    char buf[MAX_BYTES_BUFFER];
    buffer = buf;
    this->gameClient = gameClient;
}

bool Client::init(){

    if(create() < 0){return false;}
    if(connectToServer() < 0){return false;}

    std::thread read = std::thread(&Client::readThread, this);
    std::thread send = std::thread(&Client::sendThread, this);
    std::thread dispatch = std::thread(&Client::dispatchThread, this);
    dispatch.join();
    read.join();
    send.join();
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
        socketFD = -1;
    }

    return socketFD;
}

//DESTROY
//=========================================================================================
Client::~Client() {
    disconnectFromServer();
}