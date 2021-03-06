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
    void notifyEndOfGame();
    void processPlayerDeath(int id);
    void notifyGameStart();
    void directSendToServer(string basicString);
    bool hasDeadPlayer();

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

    void connected();

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
    void updateMusic();
    void updateRendering();
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
    void initSoundSystem();
    void initLoggerMenu();
    void init() override ;
    void initSDL();
    void initSDLMixer();
    void initGameMusic();
    void initYouDiedOrDisconnectedMusic();
    

    //ATRIBUTES
    //===============================
    string color = "";
    string user = "";

    string GAME_MUSIC_PATH = "resources/sfx/music/soundtrack.wav";
    string YOU_DIED_OR_DISCONNECTED_MUSIC_PATH = "resources/sfx/music/Curb_Your_Enthusiasm_theme_song.wav";
    string VICTORY_MUSIC_PATH = "resources/sfx/music/we_are_the_champions.wav";
    string LOSSING_MUSIC_PATH = "resources/sfx/music/dun_dun_dun.wav";
    int END_SCREEN_FRAMES = 1000;

    SoundWrapper* gameMusic = nullptr;

    static bool hasInstance;

    bool gameStarted = false;
    bool playerDied = false;
    bool endOfGame = false;
    bool loggedIn = false;
    bool disconnect = false;
    bool gameWon = false;
    bool gameLost = false;


    std:: mutex mu;
    std:: mutex controllerMutex;
    std::condition_variable waitForConnection;
    std::thread clientConnectionThread;

    LoggerMenu* loggerMenu = nullptr;
    Client* client = nullptr;
    std::list<Sendable*>* previousPackages = nullptr;
    std::map<std::string, TextureWrapper*> loadedTexturesMap;
    std::map<string, SoundWrapper *> loadedSoundsMap;

    void initVictoryMusic();

    void initLossingMusic();
};

#endif //GAME_GAMECLIENT_H_
