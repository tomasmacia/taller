#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include "Manager.h"
#include "LevelBuilder.h"
#include "Game.h"
#include "ToClientPack.h"
#include "../net/Server.h"

class Server;

class GameServer : public  Game{
public:

    // *************************
    // ******* SINGLETON *******
    // *************************

    static GameServer &getInstance() {
        static GameServer instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        hasInstance = true;
        return instance;
    }
    GameServer(GameServer const &) = delete;
    void operator=(GameServer const &) = delete;


    // *************************
    // ******* METHODS *********
    // *************************

    void start() override ;
    void endLevel();
    int getCurrentLevelWidth();
    std::string validateLogin(std::string user, std::string pass, int userId);
    void reconstructInput(std::string action, std::string id);
    void addNewIDToGame(int id);

    static bool isActive(){
        return hasInstance;
    }

    // *************************
    // ******* WRAPPERS ********
    // *************************

    Manager* getManager() {
        return manager;
    }
    Server* getServer() {
        return server;
    }

protected:
    void init() override ;
    void destroy() override ;

private:
    GameServer() {
        init();
    }
    ~GameServer() {
        destroy();
    }
    void waitUntilAllPlayersAreConected();

    // inits
    void initECSManager();
    void initLevelBuilder();
    void loadValidCredenctials();   //<user,pass>
    void initServer();
    void initGameModel();

    // gameloop
    void gameLoop();
    void update();
    void sendUpdate();

    static bool hasInstance;

    std::list<ToClientPack> toClientsPackages;
    std::map<std::string,std::string> validCredentials;
    std::map<std::string,std::string> loggedPlayers;

    int amountOfConectionsNeeded;

    Server* server = nullptr;
    LevelBuilder* levelBuilder = nullptr;
    Manager* manager = nullptr;
};

#endif //GAME_GAMESERVER_H_