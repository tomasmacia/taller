//
// Created by axel on 29/10/19.
//

#include "Server.h"

Server::Server(int port) {
    portNumber = port;
}

void Server::initSocket() {

    //setup a socket and connection tools
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sendSockAddr.sin_port = htons(portNumber);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0); //TCP por internet
    bind(serverSocket, (struct sockaddr*) &sendSockAddr,sizeof(sendSockAddr));
}

void Server::open() {

    initSocket();

    //open for clients to connect
    listen(serverSocket, 5);
    socklen_t clientSockAddrSize = sizeof(clientSockAddr);
    definitiveSoket = accept(serverSocket, (sockaddr *)&clientSockAddr, &clientSockAddrSize);
    if(definitiveSoket < 0)
    {
        cout<<"fallo en conexion";
    }
    runConection();
    closeConection();
}

void Server::sendMessage(std::string message) {

    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, message.c_str());
    send(definitiveSoket, (char*)&msg, strlen(msg), 0);
}

std::string Server::reciveMessage() {

    memset(&msg, 0, sizeof(msg));//clear the buffer
    recv(definitiveSoket, (char*)&msg, sizeof(msg), 0);
    std::string message(msg);
    return message;
}


void Server::runConection() {

    bool conectionOn = true;
    std::string recivedMessage = "";
    string data;

    cout << "Connected with client!" << endl;

    while(conectionOn)
    {
        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        recivedMessage = reciveMessage();
        if(recivedMessage == "exit")
        {
            cout << "Client has quit the session" << endl;
            conectionOn = false;
        }
        else {
            cout << "Client: " << recivedMessage << endl;
            cout << ">";
            sendMessage("chau");
        }
    }
}


void Server::closeConection() {
    close(definitiveSoket);
    close(serverSocket);
}
