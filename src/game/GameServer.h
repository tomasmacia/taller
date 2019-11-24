#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include <thread>
#include <condition_variable>
#include <mutex>

#include "../to_remove_or_modify/Manager.h"
#include "../to_remove_or_modify/LevelBuilder.h"
#include "Game.h"
#include "../net/messaging/ToClientPack.h"
#include "../enumerates/Action.h"
#include "../enumerates/Color.h"
#include "../net/messaging/User.h"

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
    void reemplazePreviousIDWith(int oldID, int newID);
    void reciveNewInput(tuple<Action,int> input);
    int getCurrentLevelWidth();
    static bool isActive();
    bool playersCanMove();
    void connectionLostWith(int id);
    bool isIDLogged(int ID);
    void sendWaitingScreen();

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
    void initWaitingScreen();
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
    bool credentialsAreValid(string user, string pass);
    bool userAlreadyLoggedIn(string user);
    bool userIsDisconnected(string user);
    bool validUser(string user);
    bool validPass(string user, string pass);
    bool userInLoggedPlayers(string user);
    bool IDInDisconnectedPlayers(string user);
    string processConectionAndEmitSuccesMessage(string user, string pass, int id);
    string processReconectionAndEmitSuccesMessage(string user, int newId);
    string getNewColor();

    //ATRIBUTES
    //===============================
    int SLEEP_TIME = 13000;
    Color currentColor = BLUE;

    static bool hasInstance;

    std::thread listenConnectionsThread;

    std::map<std::string,std::string> validCredentials;             //<name,pass>
    std::map<std::string,std::string> loggedPlayersPassByUser;      //<name,pass>
    std::map<std::string,int> loggedPlayersIDbyUser;                //<name,id>
    std::map<int,User> loggedPlayersUserByID;                       //<id,user>
    std::map<std::string,int> disconectedPlayers;                   //<name,id>

    int maxPlayers;

    ToClientPack* waitingScreenRenderable = nullptr;
    list<ToClientPack*>* waitingScreenContainer = nullptr;

    Server* server = nullptr;
    LevelBuilder* levelBuilder = nullptr;
    Manager* manager = nullptr;
};

#endif //GAME_GAMESERVER_H_