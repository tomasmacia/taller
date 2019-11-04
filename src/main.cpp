#include "game/Game.h"
#include "parser/CLIArgumentParser.h"
<<<<<<< HEAD
#include "game/LoggerMenu.h"
=======
#include "server/Client.h"
#include "server/Server.h"
#include <thread>

void accept_connections(Server* server) {
    while(1) {
        server->listen();
        server->accept();
    }
}
>>>>>>> origin/develop


int main(int argc, const char** argv) {
    CLIArgumentParser::getInstance().init(argc, argv);
<<<<<<< HEAD
    LoggerMenu* login = new LoggerMenu();
    
    if(login->open()){
        Game::getInstance().start();
    }
=======

    std::string mode = CLIArgumentParser::getInstance().getModeType();

    if (mode == "client") {
        Client *client = new Client();

        client->create();
        client->connectToServer();
        client->send();
        client->receive();
        client->disconnectFromServer();

    } else if (mode == "server") {
        Server *server = new Server();

        server->create();
        server->bind();
        std::thread hola = std::thread(&accept_connections, server);

        hola.join();
        server->shutdown();
        server->close();

    } else {
        // handle mode type
    }

    //Game::getInstance().start();
>>>>>>> origin/develop

    return 0;
}
