//
// Created by axelmpm on 1/12/19.
//

#include "ScoreAppearance.h"
#include <iostream>

ScoreAppearance::ScoreAppearance(ScreenPosition *screenPosition, Score *score) : Appearance(screenPosition) {
    this->score = score;
}

void ScoreAppearance::update() {
    //TODO
}

Renderable *ScoreAppearance::actuallyGenerateRenderable() {
    return nullptr; //TODO
}

void ScoreAppearance::loadNextImage() {
    //TODO
}

list<Sendable*> ScoreAppearance::numerRenderabls(int score,list<Sendable *> sendables ){
    list<Sendable*> sendable2 = sendables;
    bool asd =true;
    string path1;
    int score_ = score;
    int x_ = positionXscore;
    int y= positionYscore;
    if (score_>=0 ) {

        while(asd)
        {

            ImageSize imageSize1;
            int resto = score_ % 10;


            if (resto == 0){
                path1 = "resources/sprites/score/zero.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
          //                   std::cerr << "0"<< std::endl;
            }
             if (resto == 1)
            {
                path1 = "resources/sprites/score/one.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
          //                  std::cerr << "1"<< std::endl;
            }
             if (resto == 2)
            {
                path1 = "resources/sprites/score/two.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
         //                  std::cerr << "2"<< std::endl;
            }
             if (resto == 3)
            {
                path1 = "resources/sprites/score/three.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
         //                  std::cerr << "3"<< std::endl;
            }
             if (resto == 4)
            {
                path1 = "resources/sprites/score/four.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
           //                std::cerr << "4"<< std::endl;
            }
             if (resto == 5)
            {
                path1 = "resources/sprites/score/five.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
          //               std::cerr << "5"<< std::endl;
            }
             if (resto == 6)
            {
                path1 = "resources/sprites/score/six.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
           //                 std::cerr << "6"<< std::endl;
            }
             if (resto == 7)
            {
                path1 = "resources/sprites/score/seven.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
           //               std::cerr << "7"<< std::endl;
            }
             if (resto == 8)
            {
                path1 = "resources/sprites/score/eigth.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
          //                std::cerr << "8"<< std::endl;
            }
             if (resto == 9)
            {
                path1 = "resources/sprites/score/nine.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
            //              std::cerr << "9"<< std::endl;
            }
            int imageWidth1 = imageSize1.width;
            int imageHeight1 = imageSize1.height;
            

            Rect src1 = {0,0,imageWidth1,imageHeight1};
            Rect dst1 = {x_,y,16,16 };

            x_-= 16;


            auto c= new Sendable(new Renderable(path1, src1, dst1, false),nullptr);
            sendable2.push_back(c);

            score_ -= resto;
            if (score_ <= 0){
                asd =false;
            }
            score_ = score_/10;

        }
        std::cerr << score<< std::endl;
    }
    return sendable2;
}