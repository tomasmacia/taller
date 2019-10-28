//
// Created by Tomás Macía on 26/10/2019.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H



class Client {
public:
    Client() {}
    ~Client() {};
    int create();
    int connectToServer();
    int disconnectFromServer();
    int send();
    int receive();

private:
    int socketFD;

    void error(const char* msg);
};


#endif //GAME_CLIENT_H
