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
#include "Action.h"
#include "Game.h"
#include "ToClientPack.h"
#include "../net/Server.h"
#include "GameClient.h"


class Controller {
public:
    Controller(Game* game);

    //API
    //===============================
    string pollAndProcessInput();
    bool hasNewInput();

    //DATA TRANSFER INTERFACE
    //===============================
    void sendUpdate(std::list<ToClientPack> toClientsPackages, Server* server);
    std::string getSuccesfullLoginMessage(int userId);
    std::string getInvalidCredentialMessage();
    std::string getServerFullMessage();
    std::string getAlreadyLoggedInMessage();

    //SETTERS
    //===============================
    void setRenderable(ToClientPack package){
        currentPackagesToRender.push_back(package);
    }

    void setInput(tuple<Action,int> input){
        return currentInput.push_back(input);
    }

    //GETTERS
    //===============================
    std::list<std::tuple<Action,int>> getInput() {
        return currentInput;
    }
    std::list<ToClientPack> getPackages(){
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

    //ATRIBUTES
    //===============================
    //el input ahora es una tupla (Action, id)
    std::list<std::tuple<Action,int>> currentInput;
    std::list<ToClientPack> currentPackagesToRender;

    SDL_Event sdlEvent;
    ObjectSerializer objectSerializer;

    std::map<SDL_Scancode, Action> actions;
    std::map<std::string, SDL_Scancode> scancodes;

    Game* game = nullptr;
};

#endif //GAME_CONTROLLER_H
