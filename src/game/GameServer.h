#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include "Manager.h"
#include "LevelBuilder.h"
#include "Game.h"
#include "ToClientPack.h"
#include "../net/Server.h"
#include "Action.h"

class Server;

class GameServer : public  Game{
public:

    //SINGLETON
    //===============================
    static GameServer &getInstance() {
        static GameServer instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        hasInstance = true;
        return instance;
    }
    GameServer(GameServer const &) = delete;
    void operator=(GameServer const &) = delete;

    //ENTRY POINT
    //===============================
    void start() override;

    //API
    //===============================
    void endLevel();
    std::string validateLogin(std::string user, std::string pass, int userId);
    void addNewIDToGame(int id);
    void reciveNewInput(tuple<Action,int> input);
    int getCurrentLevelWidth();
    static bool isActive();

    //GETTERS
    //===============================

    Manager* getManager() {
        return manager;
    }
    Server* getServer() {
        return server;
    }

private:
    GameServer() {
        init();
    }

    //DESTROY
    //===============================
    ~GameServer() {
        destroy();
    }
    void destroy() override ;

    //LOGIN
    //===============================
    void waitUntilAllPlayersAreConected();

    //GAME LOOP
    //===============================
    void gameLoop() override ;
    void update();
    void sendUpdate();

    //INIT
    //===============================
    void initECSManager();
    void initLevelBuilder();
    void loadValidCredenctials();   //<user,pass>
    void initGameModel();
    void init() override ;

    //SERVER RELATED
    //===============================
    void startServer();
    void closeServer();

    //ATRIBUTES
    //===============================
    static bool hasInstance;

    std::thread listenThread;
    std::thread checkingConnectionsThread;

    std::map<std::string,std::string> validCredentials;
    std::map<std::string,std::string> loggedPlayers;

    int amountOfConectionsNeeded = 2; //HARCODED

    Server* server = nullptr;
    LevelBuilder* levelBuilder = nullptr;
    Manager* manager = nullptr;
};

#endif //GAME_GAMESERVER_H_