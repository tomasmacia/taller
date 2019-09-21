
#include "sprite.h"

//CONSTRUCTOR & DESTRUCTOR
Sprite::Sprite(std::string image_path,int r_transparent,int g_transparent,int b_transparent) :
_image_path(image_path), _r_transparent(r_transparent), _g_transparent(g_transparent), _b_transparent(b_transparent)
{}

//PUBLIC
std::string Sprite::getImagePath(){
    return _image_path;
}

int Sprite::getRTransparent(){
    return _r_transparent;
}

int Sprite::getGTransparent(){
    return _g_transparent;
}

int Sprite::getBTransparent(){
    return _b_transparent;
}