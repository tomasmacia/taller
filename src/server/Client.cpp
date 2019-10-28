#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_pton -> string to in_addr
#include <CLIArgumentParser.h>

void Client::error(const char *msg) {
    perror(msg);
    exit(0);
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
    }

    return socketFD;
}

int Client::disconnectFromServer() {
    close(socketFD);
    return 0;
}

int Client::send() {
    char buffer[256];

    printf("Please enter the message: ");
    fgets(buffer,255, stdin);
    int n = write(socketFD, buffer, strlen(buffer));
    if (n < 0) {
        error("ERROR writing to socket");
    }

    return socketFD;
}

int Client::receive() {
    char buffer[256];

    int n = read(socketFD, buffer, 255);
    if (n < 0) {
        error("ERROR reading from socket");
    }

    printf("%s\n", buffer);

    return socketFD;
}