//
// Created by Tomás Macía on 04/10/2019.
//

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <string>
#include "Action.h"


class Controller {
public:
    Controller() {
        init();
        bind();
    }

    ~Controller() {}

    void processInput();

    Action getInput();

private:
    void init();
    void bind();

    Action currentInput;

    SDL_Event sdlEvent;

    std::map<SDL_Scancode, Action> actions;
    std::map<std::string, SDL_Scancode> scancodes;


    template <typename K, typename V>
    V getWithDefault(const std::map<K,V> &map, const K &key, const V &defaultValue);


};





#endif //GAME_CONTROLLER_H
