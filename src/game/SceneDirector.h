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
    SceneDirector(Controller *controller, Config* config);
    ~SceneDirector();

    void initWaitingScreen();
    void initEndOfGameScreen();
    void initScoreScreen(const std::list<Character*>& players, const std::map<int,User>& loggedPlayersUserByID);
    void initDisconectionScreen();
    void initYouDiedScreen();

    void sendWaitingScreen(Server* server);
    void sendEndOfGameScreen(Server* server);
    void sendScoreScreen(Server* server);
    void renderDisconectionScreen(SDL_Renderer* renderer, std::map<std::string, TextureWrapper*>* loadedTexturesMap);
    void renderYouDiedScreen(SDL_Renderer* renderer, std::map<std::string, TextureWrapper*>* loadedTexturesMap);


    void renderVictoryScreen(SDL_Renderer *pRenderer, map<std::string, TextureWrapper *> *pMap);

    void renderLossingScreen(SDL_Renderer *pRenderer, map<std::string, TextureWrapper *> *pMap);

    void initVictoryScreen();

    void initLossingScreen();

private:
    Sendable* initScreen(string path);
    void CharacterName(int y, int id, list<Sendable *> *scoreScreenContainer, std::map<int,User> loggedPlayersUserByID);
    void renderPuntaje(int score, int x, int y,list<Sendable*>* contenedor);

    string WAITING_SCREEN_PATH = "resources/sprites/screens/waiting_for_your_teammates.png";
    string END_OF_GAME_SCREEN_PATH = "resources/sprites/screens/complete.png";
    string SCORE_SCREEN_PATH = "resources/sprites/screens/mid.png";
    string DISCONECTION_SCREEN_PATH = "resources/sprites/screens/disconnection.png";
    string VICTORY_SCREEN_PATH = "resources/sprites/screens/complete.png";
    string LOSSING_SCREEN_PATH = "resources/sprites/screens/complete.png";
    string YOU_DIED_SCREEN_PATH = "NONE";

    Sendable* scoreScreen = nullptr;
    list<Sendable*>* scoreScreenContainer = nullptr;

    Sendable* endOfGameScreen = nullptr;
    list<Sendable*>* endOfGameScreenContainer = nullptr;

    Sendable* waitingScreen = nullptr;
    list<Sendable*>* waitingScreenContainer = nullptr;

    Renderable* disconectionScreen = nullptr;
    Renderable* victoryScreen = nullptr;
    Renderable* lossingScreen = nullptr;

    Renderable* youDiedScreen = nullptr;

    Config* config = nullptr;
    Controller* controller = nullptr;
};


#endif //GAME_SCENEDIRECTOR_H
