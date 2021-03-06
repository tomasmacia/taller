//
// Created by Tomás Macía on 04/10/2019.
//

#include <SDL2/SDL_scancode.h>
#include <map>
#include <tuple>
#include <utility>



#include "Controller.h"
#include "../net/messaging/IDManager.h"
#include "../net/Server.h"
#include "../utils/MapUtils.h"

#include <iostream>

//PROCESSING
//=========================================================================================

list<string> Controller::pollAndProcessInput() {//TODO HEAVY IN PERFORMANCE
    auto gameClient = (GameClient*) game;
    Action action;
    int playerId = game->getPlayerId(); //cada pc tiene uno asignado al principio y es unico
    std::string serializedInput;
    std::list<std::string> serializedInputs;

    while (SDL_PollEvent(&sdlEvent)) {

        action = MapUtils::getOrDefault(actions, sdlEvent.key.keysym.scancode, NONE);

        //checkMovementPairs(action,sdlEvent);

        if (sdlEvent.type == SDL_QUIT) {
            game->end();

        }

        if (sdlEvent.key.keysym.sym == SDLK_m && (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0)) {
            game->pauseResumeMusic();
        }

        if (!gameClient->hasDeadPlayer()) {

            if (action == TEST && (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0)) {

                serializedInput = objectSerializer->serializeInput(action, playerId);
                gameClient->directSendToServer(serializedInput);

            }
            else {

                if ((sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0)) {

                    if (action != NONE) {
                        serializedInput = objectSerializer->serializeInput(action, playerId);
                        serializedInputs.push_back(serializedInput);
                    }
                }

                if ((sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0)) {

                    if (action == UP || action == DOWN || action == LEFT || action == RIGHT ||
                        action == NONE) {//no bloqueante
                        switch (action) {
                            case UP:
                                action = END_UP;
                                break;
                            case DOWN:
                                action = END_DOWN;
                                break;
                            case LEFT:
                                action = END_LEFT;
                                break;
                            case RIGHT:
                                action = END_RIGHT;
                                break;
                            default:
                                break;
                        }
                        serializedInput = objectSerializer->serializeInput(action, playerId);
                        serializedInputs.push_back(serializedInput);
                    }
                }
            }
        }
    }
    return serializedInputs;
}

void Controller::checkMovementPairs(Action action, SDL_Event event) {

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0){

        switch (action){
            case UP:
                upMovements.push(action);
                break;
            case DOWN:
                downMovements.push(action);
                break;
            case LEFT:
                leftMovements.push(action);
                break;
            case RIGHT:
                rigthMovements.push(action);
                break;
        }
    }
    if (event.type == SDL_KEYUP && event.key.repeat == 0) {

        switch (action) {
            case UP:
                upMovements.pop();
                break;
            case DOWN:
                downMovements.pop();
                break;
            case LEFT:
                leftMovements.pop();
                break;
            case RIGHT:
                rigthMovements.pop();
                break;
        }
    }

    if ((action == UP || action == DOWN || action == LEFT || action == RIGHT) && event.key.repeat == 0){

        cout<<"balance UP: "<<upMovements.size()<<endl;
        cout<<"balance DOWN: "<<downMovements.size()<<endl;
        cout<<"balance LEFT: "<<leftMovements.size()<<endl;
        cout<<"balance RIGHT: "<<rigthMovements.size()<<endl;
        cout<<"============="<<endl;
        cout<<endl;
    }
}

void Controller::reciveRenderables(vector<string>* serializedPagackes){
    //cout<<"DISPATCH"<<endl;
    objectSerializer->reconstructSendables(serializedPagackes, currentPackagesToSend);

    /*
    int i = 0;
    for (auto sendable : *currentPackagesToSend){
        if (sendable->hasSoundable()){
            cout<<"Se recibio para emitir: "<<sendable->_soundable->getPath()<<" ,cant total recibidos: "<<currentPackagesToSend->size()<<" | i = "<<i<<endl;
        }
        i++;
    }*/
}

//DATA TRANSFER INTERFACE
//=========================================================================================

void Controller::sendUpdate(std::list<Sendable*>* toClientsPackages, Server* server) {
    string serializedPackages = objectSerializer->serializeObjects(toClientsPackages); //TODO HEAVY IN PERFORMANCE
    server->setToBroadcast(serializedPackages);
}

std::string Controller::getSuccesfullLoginMessage(string color, int userId){
    return objectSerializer->getSuccesfullLoginMessage(color, userId);
}

std::string Controller::getInvalidCredentialMessage() {
    return objectSerializer->getInvalidCredentialMessage();
}

std::string Controller::getServerFullMessage(){
    return objectSerializer->getServerFullMessage();
}

std::string Controller::getAlreadyLoggedInMessage() {
    return objectSerializer->getAlreadyLoggedInMessage();
}

//INIT & CONSTRUCTOR
//=========================================================================================

Controller::Controller(Game* game) {
    this->game = game;
    this->objectSerializer = new ObjectSerializer(game->getConfig());
    currentPackagesToSend = new std::list<Sendable*>();
    init();
    bind();
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

void Controller::bind() {
    Bindings bindings = game->getConfig()->bindings;

    actions.insert(std::make_pair(scancodes.at(bindings.UP), UP));
    actions.insert(std::make_pair(scancodes.at(bindings.DOWN), DOWN));
    actions.insert(std::make_pair(scancodes.at(bindings.RIGHT), RIGHT));
    actions.insert(std::make_pair(scancodes.at(bindings.LEFT), LEFT));

    actions.insert(std::make_pair(scancodes.at(bindings.JUMP), JUMP));
    actions.insert(std::make_pair(scancodes.at(bindings.JUMPKICK), JUMP_KICK));
    actions.insert(std::make_pair(scancodes.at(bindings.ATTACK), PUNCH));
    actions.insert(std::make_pair(scancodes.at(bindings.CROUCH), CROUCH));
    actions.insert(std::make_pair(scancodes.at(bindings.KICK), KICK));

    actions.insert(std::make_pair(scancodes.at(bindings.TEST), TEST));
    actions.insert(std::make_pair(SDL_SCANCODE_ESCAPE, QUIT));
}

//DESTROY
//=========================================================================================
void Controller::cleanUpRenderables() {
    for (auto package: *currentPackagesToSend){
        delete package;
    }
    currentPackagesToSend->clear();
}

Controller::~Controller() {
    game = nullptr;

    cleanUpRenderables();
    delete  currentPackagesToSend;
    currentPackagesToSend = nullptr;
}

bool Controller::hasNewPackages() {
    return !currentPackagesToSend->empty();
}

void Controller::sendEndMessage(Server* server) {
    server->setToBroadcast(objectSerializer->getEndOfGameMessage());
}

void Controller::sendPlayerDiedMessage(Server* server, int id) {
    server->setToBroadcast(objectSerializer->getPlayerDiedMessage(id));
}

void Controller::sendGameStartedMessage(Server *server) {
    server->setToBroadcast(objectSerializer->getGameStartedMessage());
}

string Controller::getGameStartedMessage() {
    return objectSerializer->getGameStartedMessage();
}