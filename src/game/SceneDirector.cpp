//
// Created by axelmpm on 5/12/19.
//

#include "SceneDirector.h"
#include "../net/Server.h"

SceneDirector::SceneDirector(Controller *controller, Server* server, Config* config) {
    this->config = config;
    this->controller = controller;
    this->server = server;
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
        CharacterName( y, a->getID(),scoreScreenContainer,loggedPlayersUserByID);
        renderPuntaje(a->getScore(),config->screenResolution.width-50,y,scoreScreenContainer);

        y+=50;
    }
}

void SceneDirector::sendWaitingScreen() {
    controller->sendUpdate(waitingScreenContainer,server);
}

void SceneDirector::sendEndOfGameScreen() {
    controller->sendUpdate(endOfGameScreenContainer,server);
}

void SceneDirector::sendScoreScreen() {
    controller->sendUpdate(scoreScreenContainer,server);
}

Sendable* SceneDirector::initScreen(string path) {

    ImageSize imageSize = ImageUtils::getImageSize(path);
    int imageWidth = imageSize.width;
    int imageHeight = imageSize.height;

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

void SceneDirector::renderPuntaje(int score,int x, int y,list<Sendable*>* scoreScreenContainer){
    int score_ = score;
    bool asd =true;
    string path1;
    int x_ = x, y_= y;
    if (score >= 0 ) {

        while(asd)
        {

            Sendable* c = nullptr;
            ImageSize imageSize1;
            int resto = score_ % 10;


            if (resto == 0){
                path1 = "resources/sprites/score/zero.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //             std::cerr << "0"<< std::endl;
            }
            else if (resto == 1)
            {
                path1 = "resources/sprites/score/one.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //            std::cerr << "1"<< std::endl;
            }
            else if (resto == 2)
            {
                path1 = "resources/sprites/score/two.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //            std::cerr << "2"<< std::endl;
            }
            else if (resto == 3)
            {
                path1 = "resources/sprites/score/three.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //           std::cerr << "3"<< std::endl;
            }
            else if (resto == 4)
            {
                path1 = "resources/sprites/score/four.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //           std::cerr << "4"<< std::endl;
            }
            else if (resto == 5)
            {
                path1 = "resources/sprites/score/five.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //         std::cerr << "5"<< std::endl;
            }
            else if (resto == 6)
            {
                path1 = "resources/sprites/score/six.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //            std::cerr << "6"<< std::endl;
            }
            else if (resto == 7)
            {
                path1 = "resources/sprites/score/seven.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //          std::cerr << "7"<< std::endl;
            }
            else if (resto == 8)
            {
                path1 = "resources/sprites/score/eigth.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //          std::cerr << "8"<< std::endl;
            }
            else if (resto == 9)
            {
                path1 = "resources/sprites/score/nine.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
                //          std::cerr << "9"<< std::endl;
            }
            int imageWidth1 = imageSize1.width;
            int imageHeight1 = imageSize1.height;

            int screenWidth1 = 32;
            int screenHeight1 = 32;
            x_ -= screenHeight1;

            Rect src1 = {0,0,imageWidth1,imageHeight1};
            Rect dst1 = {x_,y_,screenWidth1,screenHeight1 };

            c= new Sendable(new Renderable(path1, src1, dst1, false), nullptr);
            scoreScreenContainer->push_back(c);

            score_ -= resto;
            if (score_ <= 0){
                asd =false;
            }
            score_ = score_/10;

        }
    }
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
}



