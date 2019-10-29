//
// Created by axel on 29/10/19.
//

#ifndef TESTCLIENT_SERVER_H
#define TESTCLIENT_SERVER_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

class Server {

public:
    Server(int port);
    void open();

    void sendMessage(std::string message);
    std::string  reciveMessage();

private:
    void initSocket();
    void runConection();
    void closeConection();

    sockaddr_in sendSockAddr;
    sockaddr_in clientSockAddr;
    int serverSocket;
    int definitiveSoket;
    char msg[2000];
    int portNumber;
};


#endif //TESTCLIENT_SERVER_H
