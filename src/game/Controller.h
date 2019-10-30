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

    ~Controller() {}

    std::string processInput();
    void sendUpdate(std::list<ToClientPack> toClientsPackages, Server* server);
    void reconstructInput(std::string action, std::string id);
    void reconstructPackage(vector<string> splitedPackage);
    std::list<std::tuple<Action,int>> getInput();
    std::list<ToClientPack> getPackages();

private:
    void init();
    void bind();
    std::string generateSerializedObj(ToClientPack package);
    std::string serializeAction(Action action);

    //el input ahora es una tupla (Action, id)
    std::list<std::tuple<Action,int>> currentInput;
    std::list<ToClientPack> currentPackagesToRender;

    SDL_Event sdlEvent;

    std::map<SDL_Scancode, Action> actions;
    std::map<std::string, SDL_Scancode> scancodes;

    Game* game = nullptr;


    template <typename K, typename V>
    V getWithDefault(const std::map<K,V> &map, const K &key, const V &defaultValue);
};

#endif //GAME_CONTROLLER_H
