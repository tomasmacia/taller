//
// Created by axelmpm on 5/12/19.
//

#ifndef GAME_SCENEDIRECTOR_H
#define GAME_SCENEDIRECTOR_H


#include "../net/messaging/Sendable.h"
#include "EntityManager.h"
#include "../net/messaging/User.h"

class Server;

class SceneDirector {

public:
    SceneDirector(Controller *controller, Server* server, Config* config);
    ~SceneDirector();

    void initWaitingScreen();
    void initEndOfGameScreen();
    void initScoreScreen(const std::list<Character*>& players, const std::map<int,User>& loggedPlayersUserByID);

    void sendWaitingScreen();
    void sendEndOfGameScreen();
    void sendScoreScreen();

private:
    Sendable* initScreen(string path);
    void CharacterName(int y, int id, list<Sendable *> *scoreScreenContainer, std::map<int,User> loggedPlayersUserByID);
    void renderPuntaje(int score, int x, int y, list<Sendable *> *scoreScreenContainer);

    string WAITING_SCREEN_PATH = "resources/sprites/screens/waiting_for_your_teammates.png";
    string END_OF_GAME_SCREEN_PATH = "resources/sprites/screens/complete.png";
    string SCORE_SCREEN_PATH = "resources/sprites/screens/mid.png";

    Sendable* scoreScreen = nullptr;
    list<Sendable*>* scoreScreenContainer = nullptr;

    Sendable* endOfGameScreen = nullptr;
    list<Sendable*>* endOfGameScreenContainer = nullptr;

    Sendable* waitingScreen = nullptr;
    list<Sendable*>* waitingScreenContainer = nullptr;

    Config* config = nullptr;
    Controller* controller = nullptr;
    Server* server = nullptr;


};


#endif //GAME_SCENEDIRECTOR_H
