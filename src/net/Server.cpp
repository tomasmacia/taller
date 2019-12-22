/* The port number is passed as an argument */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "Server.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../CLIAparser/CLIArgumentParser.h"
#include "UserConnection.h"

#define MAX_BYTES_BUFFER 2500

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

void Server::stopListening(){
    shutdown();
    LogManager::logInfo("[SERVER]: Se hace el shutdown del socket");
}

//ACTUAL DATA TRANSFER
//=========================================================================================
int Server::send(string msg, int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSOcketFD este en la lista de conexiones?

    char buff[MAX_BYTES_BUFFER]{0};
    strncpy(buff, msg.c_str(), sizeof(buff));

    int n = 0;

    while (n != MAX_BYTES_BUFFER) {
        n = ::send(someSocketFD, buff, MAX_BYTES_BUFFER, MSG_NOSIGNAL);
        //cout << "SERVER-SEND: " << buff << endl;
        if (n <= 0){
            if (errno != EAGAIN){
                error("error sending | errno: " + to_string(errno));
                beginDisconectionWith(socketIDMap.at(someSocketFD));
            }
        }
    }
    return n;
}

string Server::receive(int someSocketFD) {

    char buff[MAX_BYTES_BUFFER]{0};
    int n = 0;

    while (n != MAX_BYTES_BUFFER) {
        n = recv(someSocketFD, buff, MAX_BYTES_BUFFER, 0);
        if (n <= 0){
            if (errno != EAGAIN){
                error("error reading | errno: " + to_string(errno));
                beginDisconectionWith(socketIDMap.at(someSocketFD));
            }
            return objectSerializer->getFailure();
        }
    }

    char end = objectSerializer->getEndOfSerializationSymbol();
    char padding = objectSerializer->getPaddingSymbol();
    char start = objectSerializer->getStartSerializationSymbol();
    string failureMessage = objectSerializer->getFailure();
    std::string parsed = messageParser.extractMeaningfulMessageFromStream(buff,MAX_BYTES_BUFFER, failureMessage, start, end,padding);
    if (parsed == failureMessage){
    }
    //cout << "SERVER-READ: " << parsed << endl;
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
        if (newConnectionSocketFD >= 0){
            auto newUserConnection = addNewConnection(newConnectionSocketFD);
            connectionThreads.emplace_back(&UserConnection::start,newUserConnection);
            cout << "LISTEN THREAD: connection stablished with ID: " << newUserConnection->getId()<< endl;
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
    this->objectSerializer = new ObjectSerializer(gameServer->getConfig());
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
        error("ERROR on binding");
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
        error("ERROR on accept");
    }
    else {
        LogManager::logInfo("[SERVER]: Conexion establecida");
        printf("[SERVER]: Connection from %s on port %d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
    }
    return newClientSocketFD;
}


UserConnection* Server::addNewConnection(int newSocketFD){
    auto userConnection = new UserConnection(newSocketFD, nextConectionIDtoAssign, this,gameServer);
    this->connections.insert({ nextConectionIDtoAssign, userConnection });
    this->socketIDMap.insert({ newSocketFD, nextConectionIDtoAssign });
    nextConectionIDtoAssign++; //esto asegura que la ID sea unica

    return userConnection;
}

//ERROR
//=========================================================================================
void Server::error(string msg) {   //Cierra el server y en el destructor se cierra las conexiones
    LogManager::logError("[SERVER]: " + msg);
}

//DISCONECTION RELATED
//=========================================================================================

void Server::removeConnection(int ID){

    int toRemoveSocket = -1;
    for( auto const& [socket, id] : socketIDMap) {
        if (id == ID){
            toRemoveSocket = socket;
            break;
        }
    }

    delete connections.at(ID);
    connections.erase(ID);
    socketIDMap.erase(toRemoveSocket);
    gameServer->connectionLostWith(ID);
    cout<<"CHECKING THREAD: borre la userConnection: "<<ID<<endl;
    cout << "CHECKING THREAD: tengo "<< connections.size()<<" conexiones"<<endl;
    cout << "================================================================"<<endl;
    cout<<endl;
}

int Server::shutdown() {
    return ::shutdown(socketFD, SHUT_RDWR);
}

int Server::close() {
    return ::close(socketFD);
}


void Server::client_noBlock(int a) {
    struct timeval tv{} ;
    tv.tv_usec =10000;
    tv.tv_sec = 1;

    auto it = connections.find(a);
    if (it != connections.end()) {
        if (fcntl(it->second->getSock(),F_SETFL,O_NONBLOCK)<0){
            perror("no puedo desbloquear socket");
        }
        setsockopt(it->second->getSock(),SOL_SOCKET,SO_SNDTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
        setsockopt(it->second->getSock(),SOL_SOCKET,SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
    }
}

void Server::beginDisconectionWith(int id) {
    connections.at(id)->setConnectionOff();
}

//DESTROY
//=========================================================================================
Server::~Server() {
    for (std::map<int, UserConnection *>::iterator itr = connections.begin(); itr != connections.end(); itr++) {
        delete itr->second;
    }
}
