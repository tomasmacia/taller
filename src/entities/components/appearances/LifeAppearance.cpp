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
    Rect dst1 = {XPosition,YPosition,imageWidth1,imageHeight1};

    Renderable* c = new Renderable(base, src1, dst1, false);
    return c; 
}

Renderable *LifeAppearance::GenerateRenderableToDisconnect(bool disconnectOrDead) {

    if (disconnectOrDead){
        ImageSize imageSize1;
        imageSize1 = ImageUtils::getImageSize(lifegrey);
        int imageWidth1 = imageSize1.width;
        int imageHeight1 = imageSize1.height;

        Rect src1 = {0,0,imageWidth1,imageHeight1};
        Rect dst1 = {XPosition,YPosition,imageWidth1,imageHeight1};

        Renderable* c = new Renderable(lifegrey, src1, dst1, false);
        return c; 
    }
    else
    {
        return nullptr;
    }
    
}

void LifeAppearance::loadNextImage() {
    if (!resetLife){
        base = life0;
        lifegrey = life0;

    }
    else {

        if((life == 0)){
            base = life0;
            life = 100;      
        }
    
        if((life >= 1 ) & (life <=20)){
            base = life20;
            lifegrey = life20grey;
        }

        if((life >= 21 ) & (life <=40)){
            base = life40;
            lifegrey = life40grey;
        }
        
        if((life >= 41 ) & (life <=60)){
            base = life60;
            lifegrey = life60grey;
        }
        
        if((life >= 61 ) & (life <=80)){
            base = life80;
            lifegrey = life80grey;
        }
        
        if((life >= 81 ) & (life <=100)){
            base = lifecomplete;
            lifegrey = lifecompletegrey;
        }
    }
}

void LifeAppearance::setYPosition(int a){
    YPosition = a;
}

void LifeAppearance::setXPosition(int a){
    XPosition = a;
}


void LifeAppearance::hit(int damage){
    if(resetLife){
        life = life - damage;
    }
}

void LifeAppearance::noLifes(){
    resetLife = false;
}

void LifeAppearance::pickColor(int a){

    switch (a)
    {
        case 0:
            life0 = "resources/sprites/score/Blue/0v2.png";
            life20 = "resources/sprites/score/Blue/20v2.png";
            life40 = "resources/sprites/score/Blue/40v2.png";
            life60 = "resources/sprites/score/Blue/60v2.png";
            life80 = "resources/sprites/score/Blue/80v2.png";
            lifecomplete = "resources/sprites/score/Blue/100v2.png";
            break;

        case 1:
            life0 = "resources/sprites/score/Red/0v2.png";
            life20 = "resources/sprites/score/Red/20v2.png";
            life40 = "resources/sprites/score/Red/40v2.png";
            life60 = "resources/sprites/score/Red/60v2.png";
            life80 = "resources/sprites/score/Red/80v2.png";
            lifecomplete = "resources/sprites/score/Red/100v2.png";
            break;

        case 2:
            life0 = "resources/sprites/score/Green/0v2.png";
            life20 = "resources/sprites/score/Green/20v2.png";
            life40 = "resources/sprites/score/Green/40v2.png";
            life60 = "resources/sprites/score/Green/60v2.png";
            life80 = "resources/sprites/score/Green/80v2.png";
            lifecomplete = "resources/sprites/score/Green/100v2.png";
            break;

        default:
            life0 = "resources/sprites/score/Yellow/0v2.png";
            life20 = "resources/sprites/score/Yellow/20v2.png";
            life40 = "resources/sprites/score/Yellow/40v2.png";
            life60 = "resources/sprites/score/Yellow/60v2.png";
            life80 = "resources/sprites/score/Yellow/80v2.png";
            lifecomplete = "resources/sprites/score/Yellow/100v2.png";
            break;
    }
    life20grey = "resources/sprites/score/disconnect/20v2.png";
    life40grey = "resources/sprites/score/disconnect/40v2.png";
    life60grey = "resources/sprites/score/disconnect/60v2.png";
    life80grey = "resources/sprites/score/disconnect/80v2.png";
    lifecompletegrey = "resources/sprites/score/disconnect/100v2.png";
    loadNextImage();

}