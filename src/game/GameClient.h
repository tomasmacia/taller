#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

#include <map>
#include "list"
#include <thread>
#include <condition_variable>
#include <mutex>

#include "../net/messaging/Renderable.h"
#include "Game.h"
#include "../net/Client.h"
#include "../net/messaging/Renderable.h"

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
    void notifyAboutClientConectionToServerAttemptDone();
    void end() override ;
    void render();
    void disconnected();
    
    void reciveRenderables(vector<string>* serializedPages);

    static bool isActive(){
        return hasInstance;
    }

    //SETTERS
    //===============================
    void setLogged(){
        loggedIn = true;
    }

    void setPlayerName(string name){
        this->user = name;
    }

    void setPlayerColor(string color){
        this->color = color;
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
    void erasePreviousPackages();

    void clearMaps();
    //GAME LOOP
    //===============================
    void gameLoop() override ;
    void pollAndSendInput();
    void renderAllPackages();

    //CLIENT RELATED
    //===============================
    void startClient();
    void closeClient();
    bool hasClientAttemptedConection();
    void waitUntilConnectionStablished();
    void disconnectScreen();

    //INIT
    //===============================
    void initInputSystem();
    void initRenderingSystem();
    void initScreens();
    void initSoundSystem();
    void initLoggerMenu();
    void init() override ;
    void initSDL();
    void initSDLMixer();

    

    //ATRIBUTES
    //===============================
    string color = "";
    string user = "";

    static bool hasInstance;

    bool loggedIn = false;
    bool disconnect = false;

    std:: mutex mu;
    std:: mutex controllerMutex;
    std::condition_variable waitForConnection;
    std::thread clientConnectionThread;

    TextureWrapper* disconectionScreen = nullptr;

    LoggerMenu* loggerMenu = nullptr;
    Client* client = nullptr;
    std::list<Sendable*>* previousPackages = nullptr;
    std::map<std::string, TextureWrapper*> loadedTexturesMap;
    std::map<string, SoundWrapper *> loadedSoundsMap;
};

#endif //GAME_GAMECLIENT_H_
