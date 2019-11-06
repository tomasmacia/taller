#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

#include <map>
#include "list"
#include <thread>
#include <condition_variable>
#include <mutex>

#include "ToClientPack.h"
#include "Game.h"
#include "../net/Client.h"
#include "ToClientPack.h"

class LoggerMenu;
class Client;

class GameClient : public  Game{
public:

    //SINGLETON
    //===============================
    static GameClient &getInstance() {
        static GameClient instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        hasInstance = true;
        return instance;
    }
    GameClient(GameClient const &) = delete;
    void operator=(GameClient const &) = delete;

    //ENTRY POINT
    //===============================
    void start() override;

    //API
    //===============================
    void setServerAknowledgeToLogin(MessageId id);
    void setPlayerId(int id);
    void reciveRenderable(ToClientPack* package);
    void notifyAboutClientConectionToServerAttemptDone();
    void end() override ;
    bool alreadyLoggedIn();

    static bool isActive(){
        return hasInstance;
    }

    //SETTERS
    //===============================
    void setLogged(){
        loggedIn = true;
    }

private:
    GameClient() {
        init();
    }

    //DESTROY
    //===============================
    ~GameClient() {
        destroy();
    }
    void destroy() override ;
    void clearTextureMap();

    //GAME LOOP
    //===============================
    void gameLoop() override ;
    void pollAndSendInput();
    void render();
    void renderAllPackages();

    //CLIENT RELATED
    //===============================
    void startClient();
    void closeClient();
    bool hasClientAttemptedConection();
    void waitUntilConnectionStablished();

    //INIT
    //===============================
    void initInputSystem();
    void initRenderingSystem();
    void initLoggerMenu();
    void init() override ;

    //ATRIBUTES
    //===============================
    static bool hasInstance;
    bool loggedIn = false;

    std:: mutex mu;
    std::condition_variable waitForConnection;
    std::thread clientConnectionThread;

    LoggerMenu* loggerMenu = nullptr;
    Client* client = nullptr;
    std::map<std::string, TextureWrapper*> loadedTexturesMap;
};

#endif //GAME_GAMECLIENT_H_
