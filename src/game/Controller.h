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
#include <mutex>
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

        /*string action;
        switch (std::get<0>(input)){
            case UP:
                action = "UP";
                break;
            case END_UP:
                action = "END_UP";
                break;
            case DOWN:
                action = "DOWN";
                break;
            case END_DOWN:
                action = "END_DOWN";
                break;
            case LEFT:
                action = "LEFT";
                break;
            case END_LEFT:
                action = "END_LEFT";
                break;
            case RIGHT:
                action = "RIGHT";
                break;
            case END_RIGHT:
                action = "END_RIGHT";
                break;
        }

        cout<<"INPUT RECIBIDA: ACTION: "<<action<<" ID: "<<std::get<1>(input)<<endl;*/
        mu.lock();
        currentInput->push_back(input);
        mu.unlock();
    }

    //GETTERS
    //===============================
    std::list<std::tuple<Action,int>> getACopyOfNewInputs() {
        std::list<std::tuple<Action,int>> copy;
        mu.lock();
        if (!currentInput->empty()){
            copy = *currentInput;
        }
        mu.unlock();
        return copy;
    }
    std::list<Sendable*>* getPackages(){
        return currentPackagesToSend;
    }

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

    std::mutex mu;

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
