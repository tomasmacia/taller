//
// Created by axel on 29/10/19.
//

#ifndef TESTEANDOSOCKETSYTHREADS_CLIENT_H
#define TESTEANDOSOCKETSYTHREADS_CLIENT_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
using namespace std;

class Client {

public:
    Client(const char *ip,int port);
    void beginConnection();

    void sendMessage(std::string message);
    std::string  reciveMessage();

private:
    void initSocket();
    void runConection();
    void closeConection();

    sockaddr_in sendSockAddr;
    int clientSocket;
    char msg[2000];
    int portNumber;
    const char * serverIpAdress;
};


#endif //TESTEANDOSOCKETSYTHREADS_CLIENT_H
