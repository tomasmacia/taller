//
// Created by axelmpm on 1/12/19.
//

#include "ScoreAppearance.h"
#include "../../../game/GameServer.h"
#include <iostream>

ScoreAppearance::ScoreAppearance(ScreenPosition *screenPosition, Score *score) : Appearance(screenPosition) {
    this->score = score;
}

void ScoreAppearance::update() {
    //TODO
}

Renderable *ScoreAppearance::actuallyGenerateRenderable() {
    return nullptr;
}

void ScoreAppearance::loadNextImage() {
    //TODO
}

list<Sendable *>  ScoreAppearance::numerRenderabls(int score,list<Sendable *> sendables ){
    bool asd =true;
    string path1;
    int score_ = score;
    int x_ = positionXscore;
    int y= positionYscore;
    if (score_>=0 ) {

        for (int i = 0; i < 5; i++)
        {
            ImageSize imageSize1;
            int resto = score_ % 10;

            if (resto <= 0){
                path1 = GameServer::getInstance().getConfig()->score.zero;

                imageSize1 = ImageUtils::getImageSize(path1);
          //                   std::cerr << "0"<< std::endl;
            }
             if (resto == 1)
            {
                path1 = GameServer::getInstance().getConfig()->score.one;

                imageSize1 = ImageUtils::getImageSize(path1);
          //                  std::cerr << "1"<< std::endl;
            }
             if (resto == 2)
            {
                path1 = GameServer::getInstance().getConfig()->score.two;

                imageSize1 = ImageUtils::getImageSize(path1);
         //                  std::cerr << "2"<< std::endl;
            }
             if (resto == 3)
            {
                path1 = GameServer::getInstance().getConfig()->score.three;

                imageSize1 = ImageUtils::getImageSize(path1);
         //                  std::cerr << "3"<< std::endl;
            }
             if (resto == 4)
            {
                path1 = GameServer::getInstance().getConfig()->score.four;

                imageSize1 = ImageUtils::getImageSize(path1);
           //                std::cerr << "4"<< std::endl;
            }
             if (resto == 5)
            {
                path1 = GameServer::getInstance().getConfig()->score.five;

                imageSize1 = ImageUtils::getImageSize(path1);
          //               std::cerr << "5"<< std::endl;
            }
             if (resto == 6)
            {
                path1 = GameServer::getInstance().getConfig()->score.six;

                imageSize1 = ImageUtils::getImageSize(path1);
           //                 std::cerr << "6"<< std::endl;
            }
             if (resto == 7)
            {
                path1 = GameServer::getInstance().getConfig()->score.seven;

                imageSize1 = ImageUtils::getImageSize(path1);
           //               std::cerr << "7"<< std::endl;
            }
             if (resto == 8)
            {
                path1 = GameServer::getInstance().getConfig()->score.eight;

                imageSize1 = ImageUtils::getImageSize(path1);
          //                std::cerr << "8"<< std::endl;
            }
             if (resto == 9)
            {
                path1 = GameServer::getInstance().getConfig()->score.nine;

                imageSize1 = ImageUtils::getImageSize(path1);
            //              std::cerr << "9"<< std::endl;
            }
            int imageWidth1 = imageSize1.width;
            int imageHeight1 = imageSize1.height;
            

            Rect src1 = {0,0,imageWidth1,imageHeight1};
            Rect dst1 = {x_,y,16,16 };

            x_-= 16;

            Sendable* c= new Sendable(new Renderable(path1, src1, dst1, false),nullptr);
            sendables.push_back(c);

            score_ -= resto;

            score_ = score_/10;

        }
    }
    return sendables;
}