#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <CLIArgumentParser.h>
#include <thread>
#include "../LogLib/LogManager.h"

#define MAX_BYTES_BUFFER 4096


//NUESTRO CODIGO
//===============================================================================================

void Client::setToSend(std::string message){
    mu.lock();
    toSendMessagesQueue.push_back(message);
    mu.unlock();
}

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
    return extractMessageFromStream();
}

void Client::readThread() {
    while(clientOn) {
        mu.lock();
        incomingMessage = this->receive();
        incomingMessagesQueue.push_back(incomingMessage);
        mu.unlock();
    }
}

void Client::sendThread() {
    while(clientOn) {
        mu.lock();
        toSendMessage = toSendMessagesQueue.front();
        toSendMessagesQueue.pop_front();
        this->send(toSendMessage);

        if (connectionOff()) {
            disconnectFromServer();
            mu.unlock();            //TODO, ojo aca
            break;
        }
        mu.unlock();
    }
}

bool Client::connectionOff(){
    int error_code;
    socklen_t error_code_size = sizeof(error_code);
    if (getsockopt(socketFD, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size) < 0){
        clientOn = false;
        return true;
    }
    return false;
}

std::string Client::extractMessageFromStream(){

    std::string stringedBuffer = buffer;
    std::string delimiter = "_" + END_SERIALIZATION_SIMBOL;
    std::string message = stringedBuffer.substr(0, stringedBuffer.find(delimiter));

    //le quito al buffer lo que acabo de parsear
    int messageLength = message.length();
    std::string restOfBuffer = stringedBuffer.substr(stringedBuffer.find(delimiter),
                                                     stringedBuffer.length() - messageLength);
    //(TODO) QUIZAS SEA COSTOSO A LA LARGA EN RECURSOS PORQUE SE HACE TODO EL TIEMPO ESTO
    char* cleanedBuf;
    strcpy(cleanedBuf, restOfBuffer.c_str());
    buffer = cleanedBuf;

    return message;
}

int Client::disconnectFromServer() {
    close(socketFD);
    return 0;
}

bool Client::init(){

    if(create() < 0){return false;}
    if(connectToServer() < 0){return false;}

    std::thread read = std::thread(&Client::readThread, this);
    std::thread send = std::thread(&Client::sendThread, this);
    read.join();
    send.join();
}

void Client::error(const char *msg) {
    mu.lock();
    LogManager::logError(msg);
    clientOn = false;
    mu.unlock();
}

Client::Client() {
    clientOn = true;
    maxBytesBuffer = MAX_BYTES_BUFFER;
    char buf[MAX_BYTES_BUFFER];
    buffer = buf;
}

Client::~Client() {
    disconnectFromServer();
}

//IMPLEMENTACION STANDART DE SOCKETS
//===============================================================================================

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