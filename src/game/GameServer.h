#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include <thread>
#include <condition_variable>
#include <mutex>

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
    bool playersCanMove();
    void connectionLostWith(int id);
    bool isIDLogged(int ID);

    //GETTERS
    //===============================
    int getMaxPlayers() {
        return maxPlayers;
    }

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
    void waitUnitAllPlayersConnected();
    bool notAllPlayersDisconnected();

    //CONTROLLER RELATED
    //===============================
    void initController() override ;
    void closeController();

    //LOGIN RELATED
    //===============================
    bool serverFull();
    bool userInValidCredentials(string user);
    bool passInValidCredentials(string user,string pass);
    bool userInLoggedPlayers(string user);
    bool IDInDisconnectedPlayers(string user);
    string processConectionAndEmitSuccesMessage(string user, string pass, int id);
    string processReconectionAndEmitSuccesMessage(string user, int newId);

    //ATRIBUTES
    //===============================
    static bool hasInstance;

    std::thread listenConnectionsThread;

    std::map<std::string,std::string> validCredentials;             //<user,pass>
    std::map<std::string,std::string> loggedPlayersPassByUser;      //<user,pass>
    std::map<std::string,int> loggedPlayersIDbyUser;                //<id,user>
    std::map<int,std::string> loggedPlayersUserByID;                //<user,id>
    std::map<std::string,int> disconectedPlayers;                   //<user,id>

    int maxPlayers;

    Server* server = nullptr;
    LevelBuilder* levelBuilder = nullptr;
    Manager* manager = nullptr;
};

#endif //GAME_GAMESERVER_H_