#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

#include <map>
#include "list"

#include "ToClientPack.h"
#include "Game.h"
#include "../net/Client.h"

class GameClient : public  Game{
public:
    // *************************
    // ******* SINGLETON *******
    // *************************

    static GameClient &getInstance() {
        static GameClient instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        hasInstance = true;
        return instance;
    }
    GameClient(GameClient const &) = delete;
    void operator=(GameClient const &) = delete;


    // *************************
    // ******* METHODS *********
    // *************************

    void start() override;
    void reconstructPackage(vector<string> splitedPackage);
    void sendAknowledgeToLogerMenu(int id);
    void setPlayerId(int id);

    static bool isActive(){
        return hasInstance;
    }

    // *************************
    // ******* WRAPPERS ********
    // *************************


protected:
    void init() override ;
    void destroy() override ;

private:
    GameClient() {
        init();
    }
    ~GameClient() {
        destroy();
    }
    void clearTextureMap();

    // gameloop
    void pollAndSendInput();
    void render();
    void renderAllPackages();

    static bool hasInstance;

    LoggerMenu* loggerMenu = nullptr;
    Client* client = nullptr;
    std::map<std::string, TextureWrapper*> loadedTexturesMap;;
};

#endif //GAME_GAMECLIENT_H_
