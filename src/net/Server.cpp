/* The port number is passed as an argument */
#include "Server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <CLIArgumentParser.h>
#include "UserConnection.h"

#define MAX_BYTES_BUFFER 128

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
    for (std::pair<int, UserConnection*> element : connections) {
        element.second->setToSendMessage(message);
    }
}

//ACTUAL DATA TRANSFER
//=========================================================================================
int Server::send(string msg, int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSOcketFD este en la lista de conexiones?

    char buff[MAX_BYTES_BUFFER]{0};
    strncpy(buff, msg.c_str(), sizeof(buff));
    buff[sizeof(buff) - 1] = 0;

    return ::send(someSocketFD, buff, strlen(buff), MSG_NOSIGNAL);
}

vector<string> Server::receive(int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSocketFD este en la lista de conexiones?

    //INIT
    //=================================
    char buff[MAX_BYTES_BUFFER];
    size_t size = MAX_BYTES_BUFFER;
    //=================================

    recv(someSocketFD, buff, size, 0);
    //cout <<"leido: "<< buff << endl;

    vector<string> m = messageParser.extractMeaningfulMessagesFromStream(buff, objectSerializer);
    //cout << "cantidad completos: "<<m.size()<<endl;
    //for (auto a: m){
    //cout<<"resultado: "<<a<<endl;
    //}
    //cout<<"========================="<<endl;
    //cout<<endl;
    return m;
}

//THREADS
//=========================================================================================
void Server::listenThread(){

    while (gameServer->isOn()) {
        if (connections.size() < maxConnections && listen() > 0) {
            cout<<"LISTEN THREAD: esperando conexion"<<endl;
            cout << "================================================================"<<endl;
            cout<<endl;
            auto newUserConnection = accept();
            if (newUserConnection != nullptr) {
                connectionThreads.push_back(std::thread(&UserConnection::start,newUserConnection));
                cout << "LISTEN THREAD: connection stablished: " << newUserConnection->getId()<< endl;
                cout << "================================================================"<<endl;
                cout<<endl;
            }
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

    ::listen(socketFD, this->maxConnections);
    return socketFD;
}

UserConnection* Server::accept() {                  //INSTANCIA Y AGREGA CONECCION AL MAP

    struct sockaddr_in clientAddress{};
    socklen_t clientAddressSize = sizeof(clientAddress);
    UserConnection* userConnection = nullptr;

    int newClientSocketFD = ::accept(socketFD, (struct sockaddr *) &clientAddress, &clientAddressSize);
    if (newClientSocketFD < 0) {
        //error("ERROR on accept");
    } else {
        printf("[SERVER]: Connection from %s on port %d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        userConnection = new UserConnection(newClientSocketFD, nextConectionIDtoAssign, this,gameServer);
        this->connections.insert({ nextConectionIDtoAssign, userConnection });
        nextConectionIDtoAssign++; //esto asegura que la ID sea unica
    }
    return userConnection;
}

//ERROR
//=========================================================================================
void Server::error(const char *msg) {   //Cierra el server y en el destructor se cierra las conexiones
    LogManager::logError(msg);
    serverOn = false;
}

//DISCONECTION RELATED
//=========================================================================================

void Server::removeConnection(int id){
    delete connections.at(id);
    cout<<"CHECKING THREAD: borre la connection:"<<id<<endl;
    cout << "CHECKING THREAD: tengo "<< connections.size()<<" conecciones"<<endl;
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


































//int main(int argc, char *argv[]) {
//    char buffer[256];
//    struct sockaddr_in serv_addr;
//    int n;
//    if (argc < 2) {
//        fprintf(stderr,"ERROR, no port provided\n");
//        exit(1);
//    }
//    // create a socket
//    int sockfd =  socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0)
//        error("ERROR opening socket");
//
//    // clear address structure
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//
//    int portNumber = atoi(argv[1]);
//
//    /* setup the host_addr structure for use in bind call */
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = INADDR_ANY;
//    serv_addr.sin_port = htons(portNumber);
//
//    if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//        error("ERROR on binding");
//    }
//
//
//    // This listen() call tells the socket to listen to the incoming connections.
//    // The listen() function places all incoming connection into a backlog queue
//    // until accept() call accepts the connection.
//    // Here, we set the maximum size for the backlog queue to 5.
//    listen(sockfd,5);
//
//    // The accept() call actually accepts an incoming connection
//    struct sockaddr_in clientAddress;
//    socklen_t clientAddressSize = sizeof(clientAddress);
//
//    // This accept() function will write the connecting client's address info
//    // into the the address structure and the size of that structure is clilen.
//    // The accept() returns a new socket file descriptor for the accepted connection.
//    // So, the original socket file descriptor can continue to be used
//    // for accepting new connections while the new socker file descriptor is used for
//    // communicating with the connected client.
//    int newSockfd = accept(sockfd, (struct sockaddr *) &clientAddress, &clientAddressSize);
//    if (newSockfd < 0) {
//        error("ERROR on accept");
//    }
//
//    printf("server: got connection from %s port %d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
//
//
//    // This send() function sends the 13 bytes of the string to the new socket
//    send(newSockfd, "Hello, world!\n", 13, 0);
//
//    bzero(buffer, 256);
//
//    n = read(newSockfd, buffer, 255);
//    if (n < 0) error("ERROR reading from socket");
//    printf("Here is the message: %s\n", buffer);
//
//    close(newSockfd);
//    close(sockfd);
//    return 0;
//}