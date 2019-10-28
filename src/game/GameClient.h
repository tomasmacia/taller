#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
//#include "LoggerMenu.h"

class GameClient : public  Game{
public:
    // *************************
    // ******* SINGLETON *******
    // *************************

    static GameClient &getInstance() {
        static GameClient instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    GameClient(GameClient const &) = delete;
    void operator=(GameClient const &) = delete;


    // *************************
    // ******* METHODS *********
    // *************************

    void start() override;

    // *************************
    // ******* WRAPPERS ********
    // *************************

    SDL_Renderer* getRenderer(){
        return renderer;
    }

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

    // inits
    void initSDL();

    // gameloop
    void sendInput();
    void render();
    //void initLoggerMenu();
    //void openLogin();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    //LoggerMenu* loggerMenu = nullptr;

};

#endif //GAME_GAMECLIENT_H_
