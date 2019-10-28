#include "game/Game.h"
#include "parser/CLIArgumentParser.h"
#include "server/Client.h"
#include "server/Server.h"


int main(int argc, const char** argv) {
    CLIArgumentParser::getInstance().init(argc, argv);

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
        server->listen();
        server->accept();
        //server->send();
        //server->receive();
        server->shutdown();
        server->close();

    } else {
        // handle mode type
    }

    //Game::getInstance().start();

    return 0;
}
