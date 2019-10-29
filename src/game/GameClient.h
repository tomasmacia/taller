#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

#include "Game.h"
//#include "LoggerMenu.h" TODO

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

    // gameloop
    void sendInput();
    void render();
    //void initLoggerMenu(); TODO
    //void openLogin(); TODO

    static bool hasInstance;

    //LoggerMenu* loggerMenu = nullptr; TODO

};

#endif //GAME_GAMECLIENT_H_
