//
// Created by Tomás Macía on 04/10/2019.
//

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <string>
#include <list>
#include "../enumerates/Action.h"
#include "Game.h"
#include "../net/messaging/Sendable.h"
#include "../net/Server.h"
#include "GameClient.h"


class Controller {
public:
    Controller(Game* game);
    ~Controller();

    //API
    //===============================
    std::list<string> pollAndProcessInput();
    //bool hasNewInput();
    void clearAllInputs();
    void checkIfCloseRelatedInputWasPulsed();
    void reciveRenderables(vector<string>* serializedPagackes);

    //DATA TRANSFER INTERFACE
    //===============================
    void sendUpdate(std::list<Sendable*>* toClientsPackages, Server* server);
    std::string getSuccesfullLoginMessage(string color, int userId);
    std::string getInvalidCredentialMessage();
    std::string getServerFullMessage();
    std::string getAlreadyLoggedInMessage();

    //THREADS
    //===============================
    void lisentToInputForClosing();

    //SETTERS
    //===============================
    void setRenderable(Renderable* package){
        currentPackagesToRender->push_back(package);
    }

    void setInput(tuple<Action,int> input){
        return currentInput->push_back(input);
    }

    //GETTERS
    //===============================
    std::list<std::tuple<Action,int>> getACopyOfNewInputs() {
        return *currentInput;
    }
    std::list<Renderable*>* getPackages(){
        return currentPackagesToRender;
    }

private:

    //INPUT PROCESING
    //===============================
    template <typename K, typename V>
    V getWithDefault(const std::map<K,V> &map, const K &key, const V &defaultValue);

    //INIT
    //===============================
    void init();
    void bind();

    //DESTROY
    //===============================
    void cleanUpRenderables();

    //ATRIBUTES
    //===============================
    std::list<std::tuple<Action,int>>* currentInput = nullptr;
    std::list<Renderable*>* currentPackagesToRender = nullptr;
    SDL_Event sdlEvent;
    Game* game = nullptr;

    ObjectSerializer objectSerializer;
    std::map<SDL_Scancode, Action> actions;

    std::map<std::string, SDL_Scancode> scancodes;
};

#endif //GAME_CONTROLLER_H
