//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>

class UserConnection;

class Server {
public:
    Server();
    ~Server();
    int create();
    int bind();
    int listen();
    int accept();
    int send(std::string, int someSocketFD);
    int receive(int someSocketFD);
    int shutdown();
    int close();
private:
    int socketFD;
    int maxBytesBuffer;
    std::vector<UserConnection *> connections;
    int maxConnections;

    void error(const char* msg);
};


#endif //GAME_SERVER_H
