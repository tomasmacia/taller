#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include <thread>
#include <condition_variable>
#include <mutex>

#include "../to_remove_or_modify/Manager.h"
#include "../to_remove_or_modify/LevelBuilder.h"
#include "Game.h"
#include "../net/messaging/Renderable.h"
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
    std::string validateLogin(const string& user,const std::string& pass, int userId);
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

    //LOGIN RELATED
    //===============================
    bool serverFull();
    bool credentialsAreValid(const string& user, const string& pass);
    bool userAlreadyLoggedIn(const string& user);
    bool userIsDisconnected(const string& user);
    bool validUser(const string& user);
    bool validPass(const string& user, const string& pass);
    bool userInLoggedPlayers(const string& user);
    bool IDInDisconnectedPlayers(const string& user);
    string processConectionAndEmitSuccesMessage(const string& user, const string& pass, int id);
    string processReconectionAndEmitSuccesMessage(const string& user, int newId);
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

    int maxPlayers{};

    Renderable* waitingScreenRenderable = nullptr;
    list<Renderable*>* waitingScreenContainer = nullptr;

    Server* server = nullptr;
    LevelBuilder* levelBuilder = nullptr;
    Manager* manager = nullptr;
};

#endif //GAME_GAMESERVER_H_