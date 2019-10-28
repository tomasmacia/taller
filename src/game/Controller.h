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


class Controller {
public:
    Controller(Game* game);

    ~Controller() {}

    void reciveInput();
    void processInput();
    void sendInput();

    std::list<Action> getInput();

private:
    void init();
    void bind();

    std::list<Action> currentInput;

    SDL_Event sdlEvent;

    std::map<SDL_Scancode, Action> actions;
    std::map<std::string, SDL_Scancode> scancodes;

    Game* game = nullptr;


    template <typename K, typename V>
    V getWithDefault(const std::map<K,V> &map, const K &key, const V &defaultValue);
};

#endif //GAME_CONTROLLER_H
