//
// Created by axelmpm on 1/12/19.
//

#include "LifeAppearance.h"
#include <iostream>

LifeAppearance::LifeAppearance(ScreenPosition *screenPosition) : Appearance(screenPosition) {

}

void LifeAppearance::update() {
    loadNextImage();
}

Renderable *LifeAppearance::actuallyGenerateRenderable() {
    ImageSize imageSize1;

    imageSize1 = ImageUtils::getImageSize(base);
    int imageWidth1 = imageSize1.width;
    int imageHeight1 = imageSize1.height;

    Rect src1 = {0,0,imageWidth1,imageHeight1};
    Rect dst1 = {50,YPosition,imageWidth1,imageHeight1};

    Renderable* c = new Renderable(base, src1, dst1, false);
    return c; 
}

void LifeAppearance::loadNextImage() {
    if (!resetLife){
        base = "resources/sprites/score/Blue/0v2.png";
    }
    else {
        if(golpes == 5){
            base = "resources/sprites/score/Blue/0v2.png";
            golpes = 0;      
        }
    
        if(golpes == 4 ){
            base = "resources/sprites/score/Blue/20v2.png";
        }
        
        if(golpes == 3){
            base = "resources/sprites/score/Blue/40v2.png";
        }
        
        if(golpes == 2){
            base = "resources/sprites/score/Blue/60v2.png";
        }
        
        if(golpes == 1){
            base = "resources/sprites/score/Blue/80v2.png";
        }
        
        if(golpes == 0){
            base = "resources/sprites/score/Blue/100v2.png";
        }
    }
}

void LifeAppearance::setYPosition(int a){
    YPosition = a;
}


void LifeAppearance::hit(){
    if(resetLife){
        golpes++;
    }
    std::cerr << base << std::endl;  
}

void LifeAppearance::noLifes(){
    resetLife = false;
}