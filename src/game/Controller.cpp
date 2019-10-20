//
// Created by Tomás Macía on 04/10/2019.
//

#include "Controller.h"
#include "Game.h"
#include <SDL2/SDL_scancode.h>
#include <map>
#include <utility>

void Controller::processInput() {
    currentInput.clear();
    Action action;

    while (SDL_PollEvent(&sdlEvent)) {

        action = getWithDefault(actions, sdlEvent.key.keysym.scancode, NONE);

        if (sdlEvent.type == SDL_QUIT){
            currentInput.push_back(QUIT);
        }

        if( (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0)){

            if (action != NONE) {
                currentInput.push_back(action);
            }
        }

        if ((sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0 ))
        
            if (action == UP || action == DOWN || action == LEFT || action == RIGHT ||
                action == NONE) //no bloqueante
                currentInput.push_back(NONE); //para anular la accion anterior
    }
}

std::list<Action> Controller::getInput() {
    return currentInput;
}


void Controller::bind() {
    Bindings bindings = Game::getInstance().getConfig()->bindings;

    actions.insert(std::make_pair(scancodes.at(bindings.UP), UP));
    actions.insert(std::make_pair(scancodes.at(bindings.DOWN), DOWN));
    actions.insert(std::make_pair(scancodes.at(bindings.RIGHT), RIGHT));
    actions.insert(std::make_pair(scancodes.at(bindings.LEFT), LEFT));

    actions.insert(std::make_pair(scancodes.at(bindings.JUMP), JUMP));
    actions.insert(std::make_pair(scancodes.at(bindings.JUMPKICK), JUMP_KICK));
    actions.insert(std::make_pair(scancodes.at(bindings.ATTACK), PUNCH));
    actions.insert(std::make_pair(scancodes.at(bindings.CROUCH), CROUCH));
    actions.insert(std::make_pair(scancodes.at(bindings.KICK), KICK));

    actions.insert(std::make_pair(SDL_SCANCODE_ESCAPE, QUIT));
}

template <typename K, typename V>
V Controller::getWithDefault(const std::map<K,V> &map, const K &key, const V &defaultValue) {
    V value;
    auto pos = map.find(key);
    if (pos != map.end()) {
        value = pos->second;
    } else {
        value = defaultValue;
    }

    return value;
}

void Controller::init() {
    scancodes.insert(std::make_pair("A", SDL_SCANCODE_A));
    scancodes.insert(std::make_pair("a", SDL_SCANCODE_A));

    scancodes.insert(std::make_pair("B", SDL_SCANCODE_B));
    scancodes.insert(std::make_pair("b", SDL_SCANCODE_B));

    scancodes.insert(std::make_pair("C", SDL_SCANCODE_C));
    scancodes.insert(std::make_pair("c", SDL_SCANCODE_C));

    scancodes.insert(std::make_pair("D", SDL_SCANCODE_D));
    scancodes.insert(std::make_pair("d", SDL_SCANCODE_D));

    scancodes.insert(std::make_pair("E", SDL_SCANCODE_E));
    scancodes.insert(std::make_pair("e", SDL_SCANCODE_E));

    scancodes.insert(std::make_pair("F", SDL_SCANCODE_F));
    scancodes.insert(std::make_pair("f", SDL_SCANCODE_F));

    scancodes.insert(std::make_pair("G", SDL_SCANCODE_G));
    scancodes.insert(std::make_pair("g", SDL_SCANCODE_G));

    scancodes.insert(std::make_pair("H", SDL_SCANCODE_H));
    scancodes.insert(std::make_pair("h", SDL_SCANCODE_H));

    scancodes.insert(std::make_pair("I", SDL_SCANCODE_I));
    scancodes.insert(std::make_pair("i", SDL_SCANCODE_I));

    scancodes.insert(std::make_pair("J", SDL_SCANCODE_J));
    scancodes.insert(std::make_pair("j", SDL_SCANCODE_J));

    scancodes.insert(std::make_pair("K", SDL_SCANCODE_K));
    scancodes.insert(std::make_pair("k", SDL_SCANCODE_K));

    scancodes.insert(std::make_pair("L", SDL_SCANCODE_L));
    scancodes.insert(std::make_pair("l", SDL_SCANCODE_L));

    scancodes.insert(std::make_pair("M", SDL_SCANCODE_M));
    scancodes.insert(std::make_pair("m", SDL_SCANCODE_M));

    scancodes.insert(std::make_pair("N", SDL_SCANCODE_N));
    scancodes.insert(std::make_pair("n", SDL_SCANCODE_N));

    scancodes.insert(std::make_pair("O", SDL_SCANCODE_O));
    scancodes.insert(std::make_pair("o", SDL_SCANCODE_O));

    scancodes.insert(std::make_pair("P", SDL_SCANCODE_P));
    scancodes.insert(std::make_pair("p", SDL_SCANCODE_P));

    scancodes.insert(std::make_pair("Q", SDL_SCANCODE_Q));
    scancodes.insert(std::make_pair("q", SDL_SCANCODE_Q));

    scancodes.insert(std::make_pair("R", SDL_SCANCODE_R));
    scancodes.insert(std::make_pair("r", SDL_SCANCODE_R));

    scancodes.insert(std::make_pair("S", SDL_SCANCODE_S));
    scancodes.insert(std::make_pair("s", SDL_SCANCODE_S));

    scancodes.insert(std::make_pair("T", SDL_SCANCODE_T));
    scancodes.insert(std::make_pair("t", SDL_SCANCODE_T));

    scancodes.insert(std::make_pair("U", SDL_SCANCODE_U));
    scancodes.insert(std::make_pair("u", SDL_SCANCODE_U));

    scancodes.insert(std::make_pair("V", SDL_SCANCODE_V));
    scancodes.insert(std::make_pair("v", SDL_SCANCODE_V));

    scancodes.insert(std::make_pair("W", SDL_SCANCODE_W));
    scancodes.insert(std::make_pair("w", SDL_SCANCODE_W));

    scancodes.insert(std::make_pair("X", SDL_SCANCODE_X));
    scancodes.insert(std::make_pair("x", SDL_SCANCODE_X));

    scancodes.insert(std::make_pair("Y", SDL_SCANCODE_Y));
    scancodes.insert(std::make_pair("y", SDL_SCANCODE_Y));

    scancodes.insert(std::make_pair("Z", SDL_SCANCODE_Z));
    scancodes.insert(std::make_pair("z", SDL_SCANCODE_Z));

    scancodes.insert(std::make_pair("CONTROL", SDL_SCANCODE_LCTRL));
    scancodes.insert(std::make_pair("LCTRL", SDL_SCANCODE_LCTRL));

    scancodes.insert(std::make_pair("RCTRL", SDL_SCANCODE_RCTRL));

    scancodes.insert(std::make_pair("SHIFT", SDL_SCANCODE_LSHIFT));
    scancodes.insert(std::make_pair("LSHIFT", SDL_SCANCODE_LSHIFT));

    scancodes.insert(std::make_pair("RSHIFT", SDL_SCANCODE_RSHIFT));

    scancodes.insert(std::make_pair("ALT", SDL_SCANCODE_LALT));
    scancodes.insert(std::make_pair("LALT", SDL_SCANCODE_LALT));

    scancodes.insert(std::make_pair("ALTGR", SDL_SCANCODE_RALT));
    scancodes.insert(std::make_pair("RALT", SDL_SCANCODE_RALT));

    scancodes.insert(std::make_pair("ENTER", SDL_SCANCODE_RETURN));

    scancodes.insert(std::make_pair("SPACE", SDL_SCANCODE_SPACE));

    scancodes.insert(std::make_pair("UP", SDL_SCANCODE_UP));

    scancodes.insert(std::make_pair("DOWN", SDL_SCANCODE_DOWN));

    scancodes.insert(std::make_pair("LEFT", SDL_SCANCODE_LEFT));

    scancodes.insert(std::make_pair("RIGHT", SDL_SCANCODE_RIGHT));

    scancodes.insert(std::make_pair("1", SDL_SCANCODE_KP_1));
    scancodes.insert(std::make_pair("2", SDL_SCANCODE_KP_2));
    scancodes.insert(std::make_pair("3", SDL_SCANCODE_KP_3));
    scancodes.insert(std::make_pair("4", SDL_SCANCODE_KP_4));
    scancodes.insert(std::make_pair("5", SDL_SCANCODE_KP_5));
    scancodes.insert(std::make_pair("6", SDL_SCANCODE_KP_6));
    scancodes.insert(std::make_pair("7", SDL_SCANCODE_KP_7));
    scancodes.insert(std::make_pair("8", SDL_SCANCODE_KP_8));
    scancodes.insert(std::make_pair("9", SDL_SCANCODE_KP_9));
    scancodes.insert(std::make_pair("0", SDL_SCANCODE_KP_0));

}

