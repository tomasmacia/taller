//
// Created by axelmpm on 5/12/19.
//

#include "SceneDirector.h"
#include "../net/Server.h"

SceneDirector::SceneDirector(Controller *controller, Config* config) {
    this->config = config;
    this->controller = controller;
}

void SceneDirector::initWaitingScreen() {

    waitingScreenContainer = new list<Sendable*>();
    waitingScreen = initScreen(WAITING_SCREEN_PATH);
    waitingScreenContainer->push_back(waitingScreen);
}

void SceneDirector::initEndOfGameScreen(){

    endOfGameScreenContainer = new list<Sendable*>();
    endOfGameScreen = initScreen(END_OF_GAME_SCREEN_PATH);
    endOfGameScreenContainer->push_back(endOfGameScreen);
}

void SceneDirector::initScoreScreen(const std::list<Character*>& players, const std::map<int,User>& loggedPlayersUserByID) {

    scoreScreenContainer = new list<Sendable*>();
    scoreScreen = initScreen(SCORE_SCREEN_PATH);
    scoreScreenContainer->push_back(scoreScreen);

    int y = (config->screenResolution.height/2);
    for (auto a:players){

        renderPuntaje(a->getAcumulatedScore(),config->screenResolution.width-50,y,scoreScreenContainer);
        renderPuntaje(a->getScore(),config->screenResolution.width/2,y,scoreScreenContainer);
        CharacterName( y, a->getID(),scoreScreenContainer,loggedPlayersUserByID);
        y+=50;
    }
}

void SceneDirector::initDisconectionScreen() {

    disconectionScreen = initScreen(DISCONECTION_SCREEN_PATH)->_renderable;
}

void SceneDirector::initVictoryScreen() {
    victoryScreen = initScreen(VICTORY_SCREEN_PATH)->_renderable;
}

void SceneDirector::initLossingScreen() {
    lossingScreen = initScreen(LOSSING_SCREEN_PATH)->_renderable;
}

void SceneDirector::initYouDiedScreen() {

    youDiedScreen = initScreen(YOU_DIED_SCREEN_PATH)->_renderable;
}

void SceneDirector::renderVictoryScreen(SDL_Renderer *renderer, map<std::string, TextureWrapper *> *loadedTexturesMap) {
    SDL_RenderClear(renderer);
    victoryScreen->render(loadedTexturesMap);
    SDL_RenderPresent(renderer);
}

void SceneDirector::renderLossingScreen(SDL_Renderer *renderer, map<std::string, TextureWrapper *> *loadedTexturesMap) {
    SDL_RenderClear(renderer);
    lossingScreen->render(loadedTexturesMap);
    SDL_RenderPresent(renderer);
}

void SceneDirector::renderDisconectionScreen(SDL_Renderer* renderer, std::map<std::string, TextureWrapper*>* loadedTexturesMap) {
    SDL_RenderClear(renderer);
    disconectionScreen->render(loadedTexturesMap);
    SDL_RenderPresent(renderer);
}

void SceneDirector::renderYouDiedScreen(SDL_Renderer* renderer, std::map<std::string, TextureWrapper*>* loadedTexturesMap) {
    SDL_RenderClear(renderer);
    youDiedScreen->render(loadedTexturesMap);
    SDL_RenderPresent(renderer);
}

void SceneDirector::sendWaitingScreen(Server* server) {
    controller->sendUpdate(waitingScreenContainer,server);
}

void SceneDirector::sendEndOfGameScreen(Server* server) {
    controller->sendUpdate(endOfGameScreenContainer,server);
}

void SceneDirector::sendScoreScreen(Server* server) {
    controller->sendUpdate(scoreScreenContainer,server);
}

Sendable* SceneDirector::initScreen(string path) {

    //ImageSize imageSize = ImageUtils::getImageSize(path);
    int imageWidth = 500;
    int imageHeight = 375;

    int screenWidth = config->screenResolution.width;
    int screenHeight = config->screenResolution.height;

    Rect src = {0,0,imageWidth,imageHeight};
    Rect dst = {0,0,screenWidth,screenHeight};

    return new Sendable(new Renderable(path, src, dst, false), nullptr);
}

void SceneDirector::CharacterName(int y, int id,list<Sendable*>* scoreScreenContainer, std::map<int,User> loggedPlayersUserByID){
    string path1;
    ImageSize imageSize1;
    std::map<int,User>::iterator it;
    it = loggedPlayersUserByID.find(id);
    auto user = it->second.name;
    //   std::cerr << user<< std::endl;
    if (user.compare("FRAN") == 0){
        path1="resources/sprites/score/fran.png";
    }
    if (user.compare("CRIS") == 0){
        path1="resources/sprites/score/cris.png";
    }
    if (user.compare("AXEL") == 0){
        path1="resources/sprites/score/axel.png";
    }
    if (user.compare("TOMI") == 0) {
        path1="resources/sprites/score/tomi.png";
    }
    imageSize1 = ImageUtils::getImageSize(path1);
    int imageWidth1 = imageSize1.width;
    int imageHeight1 = imageSize1.height;

    Rect src1 = {0,0,imageWidth1,imageHeight1};
    Rect dst1 = {50,y,imageWidth1 * 2,imageHeight1 * 2};

    Sendable* c = new Sendable(new Renderable(path1, src1, dst1, false), nullptr);
    scoreScreenContainer->push_back(c);
}

SceneDirector::~SceneDirector() {

    if (waitingScreenContainer != nullptr){
        for (auto sendable : *waitingScreenContainer){
            delete(sendable);
        }
        delete(waitingScreenContainer);
    }

    if (endOfGameScreenContainer != nullptr){
        for (auto sendable : *endOfGameScreenContainer){
            delete(sendable);
        }
        delete(endOfGameScreenContainer);
    }

    if (scoreScreenContainer != nullptr){
        for (auto sendable : *scoreScreenContainer){
            delete(sendable);
        }
        delete(scoreScreenContainer);
    }

    delete(disconectionScreen);
    delete(youDiedScreen);
}

void SceneDirector::renderPuntaje(int score, int x, int y, list<Sendable *> *contenedor) {

    int score_ = score;
    bool asd =true;
    string path1;
    int x_ = x, y_= y;
    Sendable* c = nullptr;
    if (score >= 0 ) {

        while(asd)
        {

            int resto = score_ % 10;

            if (resto == 0){
                path1 = config->score.zero;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 1)
            {
                path1 = config->score.one;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 2)
            {
                path1 = config->score.two;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 3)
            {
                path1 = config->score.three;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 4)
            {
                path1 = config->score.four;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 5)
            {
                path1 = config->score.five;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 6)
            {
                path1 = config->score.six;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 7)
            {
                path1 = config->score.seven;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 8)
            {
                path1 = config->score.eight;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            if (resto == 9)
            {
                path1 = config->score.nine;

                //imageSize1 = ImageUtils::getImageSize(path1);
            }
            int imageWidth1 = 16;
            int imageHeight1 = 16;

            int screenWidth1 = 32;
            int screenHeight1 = 32;
            x_ -= screenHeight1;

            Rect src1 = {0,0,imageWidth1,imageHeight1};
            Rect dst1 = {x_,y_,screenWidth1,screenHeight1 };

            c = new Sendable(new Renderable(path1, src1, dst1, false), nullptr);
            contenedor->push_back(c);

            score_ -= resto;
            if (score_ <= 0){
                asd =false;
            }
            score_ = score_/10;

        }
    }
}



