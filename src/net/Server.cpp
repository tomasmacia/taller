/* The port number is passed as an argument */
#include "Server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <CLIArgumentParser.h>
#include "UserConnection.h"

#define MAX_BYTES_BUFFER 1500

#if __APPLE__
#define MSG_NOSIGNAL 0x2000 /* don't raise SIGPIPE */
#endif	// __APPLE__


#include <iostream>

//API
//=========================================================================================

int Server::numberOfConectionsEstablished(){
    return connections.size();
}

void Server::setToSendToSpecific(string message,int connectionID){
    connections.at(connectionID)->setToSendMessage(message);
}

void Server::setToBroadcast(string message) {
    UserConnection* userConnection;
    for (std::pair<int, UserConnection*> element : connections) {
        userConnection = element.second;

        if (userConnection->hasPassedLogin()){
            userConnection->setToSendMessage(message);
        }
    }
}

//ACTUAL DATA TRANSFER
//=========================================================================================
int Server::send(string msg, int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSOcketFD este en la lista de conexiones?

    char buff[MAX_BYTES_BUFFER]{0};
    strncpy(buff, msg.c_str(), sizeof(buff));
    buff[sizeof(buff) - 1] = 0;

    int bytesSent = 0;

    while (bytesSent < MAX_BYTES_BUFFER - 1) {
        int n = ::send(someSocketFD, buff, MAX_BYTES_BUFFER - 1, MSG_NOSIGNAL);
        //if (n < 0) {
            //error("ERROR sending");
        //}

        bytesSent += n;
    }

    return bytesSent;
}

string Server::receive(int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSocketFD este en la lista de conexiones?


    char buff[MAX_BYTES_BUFFER]{0};
    //size_t size = MAX_BYTES_BUFFER;

    int bytesRead = 0;

    while (bytesRead < MAX_BYTES_BUFFER - 1) {
        int n = recv(someSocketFD, buff, MAX_BYTES_BUFFER - 1, 0);
        //if (n < 0) {
            //error("ERROR leyenendo");
       //}

        bytesRead += n;
    }

    char end = objectSerializer.getEndOfSerializationSymbol();
    char padding = objectSerializer.getPaddingSymbol();
    std::string parsed = messageParser.extractMeaningfulMessageFromStream(buff, end,padding);
    return parsed;
}

//THREADS
//=========================================================================================
void Server::listenThread(){

    while (gameServer->isOn()) {
        listen();
        cout<<"LISTEN THREAD: esperando conexion"<<endl;
        cout << "================================================================"<<endl;
        cout<<endl;
        int newConnectionSocketFD = accept();
        auto newUserConnection = addNewConnection(newConnectionSocketFD);
        if (newUserConnection != nullptr) {

            connectionThreads.push_back(std::thread(&UserConnection::start,newUserConnection));
            cout << "LISTEN THREAD: connection stablished: " << newUserConnection->getId()<< endl;
            cout << "================================================================"<<endl;
            cout<<endl;
        }
    }


    UserConnection* userConnection;
    for (auto c: connections){
        userConnection = c.second;
        userConnection->shutdown();
    }
    for (std::thread &t: connectionThreads){
        t.join();
    }
}

//INIT & CONSTRUCTOR
//=========================================================================================
Server::Server(GameServer* gameServer) {

    this->serverOn = true;
    this->maxConnections = gameServer->getMaxPlayers();
    maxBytesBuffer = MAX_BYTES_BUFFER;
    this->gameServer = gameServer;
}

void Server::init(){
    create();
    bind();
}

int Server::create() {

    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    return socketFD;
}

int Server::bind() {

    struct sockaddr_in serverAddress{};
    string strPort = CLIArgumentParser::getInstance().getServerPort();

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    serverAddress.sin_port = htons(stoi(strPort));

    if (::bind(socketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        //error("ERROR on binding");
    }
    return socketFD;
}

int Server::listen() {

    ::listen(socketFD, MAX_PENDING_CONNECTIONS);
    return socketFD;
}

int Server::accept() {                  //INSTANCIA Y AGREGA CONECCION AL MAP

    struct sockaddr_in clientAddress{};
    socklen_t clientAddressSize = sizeof(clientAddress);
    UserConnection* userConnection = nullptr;

    int newClientSocketFD = ::accept(socketFD, (struct sockaddr *) &clientAddress, &clientAddressSize);
    if (newClientSocketFD < 0) {
        //error("ERROR on accept");
    } else {
        LogManager::logInfo("[SERVER]: Conexion establecida");
        printf("[SERVER]: Connection from %s on port %d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

    }
    return newClientSocketFD;
}


UserConnection* Server::addNewConnection(int newSocketFD){
    auto userConnection = new UserConnection(newSocketFD, nextConectionIDtoAssign, this,gameServer);
    this->connections.insert({ nextConectionIDtoAssign, userConnection });
    nextConectionIDtoAssign++; //esto asegura que la ID sea unica

    return userConnection;
}

//ERROR
//=========================================================================================
void Server::error(string msg) {   //Cierra el server y en el destructor se cierra las conexiones
    LogManager::logError("[SERVER]: " + msg);
    serverOn = false;
}

//DISCONECTION RELATED
//=========================================================================================

void Server::removeConnection(int id){
    delete connections.at(id);
    cout<<"CHECKING THREAD: borre la userConnection:"<<id<<endl;
    cout << "CHECKING THREAD: tengo "<< connections.size()<<" conexiones"<<endl;
    cout << "================================================================"<<endl;
    cout<<endl;
    connections.erase(id);
    gameServer->connectionLostWith(id);
}

int Server::shutdown() {
    return ::shutdown(socketFD, SHUT_WR);
}

int Server::close() {
    return ::close(socketFD);
}

//DESTROY
//=========================================================================================
Server::~Server() {
    for(std::map<int, UserConnection*>::iterator itr = connections.begin(); itr != connections.end(); itr++) {
        delete itr->second;
    }
    shutdown();
    close();
}
