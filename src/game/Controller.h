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
#include <stack>
#include "../enumerates/Action.h"
#include "Game.h"
#include "../net/messaging/Sendable.h"
#include "GameClient.h"

class Server;
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
    void cleanUpRenderables();

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
    void setRenderable(Sendable* package){
        currentPackagesToSend->push_back(package);
    }

    void setInput(tuple<Action,int> input){
        return currentInput->push_back(input);
    }

    //GETTERS
    //===============================
    std::list<std::tuple<Action,int>> getACopyOfNewInputs() {
        return *currentInput;
    }
    std::list<Sendable*>* getPackages(){
        return currentPackagesToSend;
    }

    void untrackLastSendables();

    bool hasNewPackages();

    void sendEndMessage(Server* server);

    void sendPlayerDiedMessage(Server* server, int id);

    void sendGameStartedMessage(Server *server);

    string getGameStartedMessage();

private:

    //INIT
    //===============================
    void init();
    void bind();

    //ATRIBUTES
    //===============================
    std::list<std::tuple<Action,int>>* currentInput = nullptr;
    std::list<Sendable*>* currentPackagesToSend = nullptr;
    SDL_Event sdlEvent;
    Game* game = nullptr;

    ObjectSerializer* objectSerializer = nullptr;
    std::map<SDL_Scancode, Action> actions;

    std::map<std::string, SDL_Scancode> scancodes;

    std::stack<Action> upMovements;
    std::stack<Action> downMovements;
    std::stack<Action> leftMovements;
    std::stack<Action> rigthMovements;

    void checkMovementPairs(Action action, SDL_Event event);
};

#endif //GAME_CONTROLLER_H
