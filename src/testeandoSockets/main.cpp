#include <thread>
#include "Client.h"
#include "Server.h"

int main(int argc, char *argv[])
{
    int port = 5001;
    Server* server = new Server(port);
    Client* client = new Client("192.168.1.107",port);

    std::thread t(&Client::beginConnection,client);
    server->open();

    t.join();

    delete(client);
    delete(server);

    return 0;
}
