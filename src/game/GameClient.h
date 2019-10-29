#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

#include <map>
#include "list"

#include "ToClientPack.h"
#include "Game.h"
#include "LoggerMenu.h"

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
    void startLogin();

    // gameloop
    void pollAndSendInput();
    void render();
    void renderCadaPaquete();

    static bool hasInstance;

    std::map<std::string, TextureWrapper*> loadedTexturesMap;
    std::list<ToClientPack> packages;

    LoggerMenu* loginMenu = nullptr;
    //SocketManager* socketManager = nullptr;
};

#endif //GAME_GAMECLIENT_H_
