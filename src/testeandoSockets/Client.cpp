//
// Created by axel on 29/10/19.
//

#include "Client.h"

Client::Client(const char * ip, int port) {
    serverIpAdress = ip;
    portNumber = port;
}

void Client::initSocket() {

    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIpAdress);
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(portNumber);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //TCP por internet
}

void Client::beginConnection() {

    initSocket();

    while (true){
        //try to connect...
        int status = connect(clientSocket,(sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
        if(status < 0)
        {
            cout<<"fallo en conexion";
            continue;
        }
        runConection();
        closeConection();
        break;
    }
}

void Client::sendMessage(std::string message) {

    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, message.c_str());
    send(clientSocket, (char*)&msg, strlen(msg), 0);
}

std::string Client::reciveMessage() {

    memset(&msg, 0, sizeof(msg));//clear the buffer
    recv(clientSocket, (char*)&msg, sizeof(msg), 0);
    std::string message(msg);
    return message;
}

void Client::runConection() {

    bool conectionOn = true;
    std::string recivedMessage = "";

    cout << "Connected to the server!" << endl;
    while(conectionOn)
    {
        cout << ">";
        if(recivedMessage == "exit")
        {
            sendMessage("exit");
            conectionOn = false;
        }
        else{
            sendMessage("hola");
            cout << "Awaiting server response..." << endl;
            recivedMessage = reciveMessage();
        }

        if(recivedMessage == "exit")
        {
            cout << "Server has quit the session" << endl;
            conectionOn = false;
        }
        else{
            cout << "Server: " << recivedMessage << endl;
        }
    }
}

void Client::closeConection() {
    close(clientSocket);
}

/*
void Client::runConection() {

    bool conectionOn = true;
    std::string recivedMessage = "";

    cout << "Connected to the server!" << endl;
    while(conectionOn)
    {
        cout << ">";
        if(recivedMessage == "exit")
        {
            sendMessage("exit");
            conectionOn = false;
        }
        else{
            sendMessage("hola");
            cout << "Awaiting server response..." << endl;
            recivedMessage = reciveMessage();
        }

        if(recivedMessage == "exit")
        {
            cout << "Server has quit the session" << endl;
            conectionOn = false;
        }
        else{
            cout << "Server: " << recivedMessage << endl;
        }
    }
}*/


