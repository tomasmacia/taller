#ifndef GAME_GAMESERVER_H_
#define GAME_GAMESERVER_H_

#include <thread>
#include <condition_variable>
#include <mutex>

#include <iostream>
#include <unistd.h>
#include <utility>

#include "Game.h"
#include "EntityManager.h"
#include "LevelBuilder.h"
#include "LevelBuilder.h"
#include "Controller.h"

#include "../enumerates/Action.h"
#include "../logger/Logger.h"
#include "../logger/LogManager.h"
#include "../CLIAparser/CLIArgumentParser.h"

#include "../XMLparser/xmlparser.h"

#include "../net/Server.h"
#include "../net/messaging/IDManager.h"
#include "../net/messaging/Renderable.h"
#include "../image/ImageUtils.h"
#include "../net/messaging/User.h"
#include "../enumerates/Color.h"

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

    EntityManager* getManager() {
        return entityManager;
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
    void ScoreScreen();
    void finalScreen();
    void renderPuntaje(int score,int x, int y,list<Sendable*>* wa);
    EntityManager* initLevelBuilder();
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



    void CharacterName(int y, int id,list<Sendable*>* wa);

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

    Sendable* waitingScreenRenderable = nullptr, *scoreScreenRenderable = nullptr;
    list<Sendable*>* waitingScreenContainer = nullptr, *scoreContainer = nullptr;

    Server* server = nullptr;
    EntityManager* entityManager = nullptr;
    LevelBuilder* levelBuilder = nullptr;
};

#endif //GAME_GAMESERVER_H_