/* The port number is passed as an argument */
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <CLIArgumentParser.h>
#include "UserConnection.h"

#define MAX_BYTES_BUFFER 4096
#define MAX_CONNECTIONS 4

void Server::error(const char *msg) {
    perror(msg);
    exit(1);
}

Server::Server() {
    this->connections = {nullptr};
    this->maxConnections = MAX_CONNECTIONS; // TODO sacarlo de la config
}

int Server::create() {
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        error("ERROR opening socket");
    }

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
    if (::listen(socketFD, 4) < 0) { // TODO hardcoded MAX connections. Replace with config later
        error("ERROR on listening");
    }

    return socketFD;
}

int Server::accept() {
    struct sockaddr_in clientAddress{};
    socklen_t clientAddressSize = sizeof(clientAddress);

    int newClientSocketFD = ::accept(socketFD, (struct sockaddr *) &clientAddress, &clientAddressSize);
    if (newClientSocketFD < 0) {
        error("ERROR on accept");
    } else {
        printf("[SERVER]: Connection from %s on port %d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        auto *userConnection = new UserConnection(newClientSocketFD, (int) this->connections.size(), this);
        this->connections.push_back(userConnection);
        userConnection->init();
    }

    return newClientSocketFD;
}

int Server::send(string msg, int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSOcketFD este en la lista de conexiones?
    if (::send(someSocketFD, "Hello, world!\n", 13, 0) < 0) { // TODO msg
        error("ERROR on accept");
    }

    return someSocketFD;
}

int Server::receive(int someSocketFD) {
    // TODO REVISAR. Hay que fijarse que someSOcketFD este en la lista de conexiones?
    char buffer[MAX_BYTES_BUFFER]{0};
    int n = read(someSocketFD, buffer, MAX_BYTES_BUFFER);
    if (n < 0) {
        error("ERROR reading from socket");
    }

    printf("Here is the message: %s\n", buffer);

    return someSocketFD;
}

int Server::shutdown() {
    int shutResult = ::shutdown(socketFD, SHUT_WR);
    if (shutResult < 0){
        error("ERROR shutdown conn");
    }
    return ::shutdown(socketFD, SHUT_WR);
}

int Server::close() {
    return ::close(socketFD);
}

Server::~Server() {

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