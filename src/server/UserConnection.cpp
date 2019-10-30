//
// Created by Tomás Macía on 27/10/2019.
//

#include "UserConnection.h"
#include <iostream>
#include <thread>

UserConnection::UserConnection(int socket, int userId, Server *server) {
    this->socketFD = socket;
    this->userId = userId;
    this->server = server;
}

void UserConnection::dummyThread() {
    while(true) {
        std::cout << "read" << std::endl;
    }
}

void UserConnection::writeThread() {
    while(true) {
        std::cout << "write" << std::endl;
    }
}

void UserConnection::controlThread() {
    while(true) {
        std::cout << "control" << std::endl;
    }
}

void UserConnection::init() {
    std::thread xd = std::thread(&UserConnection::dummyThread, this);
    std::thread read = std::thread(&UserConnection::writeThread, this);
    std::thread control = std::thread(&UserConnection::controlThread, this);
    xd.join();
    read.join();
    control.join();
}
