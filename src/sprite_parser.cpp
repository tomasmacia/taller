#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite_parser.h"

//CONSTRUCTOR & DESTRUCTOR
SpriteParser::SpriteParser(std::vector <std::string>& spritePaths){
    _spritePaths = spritePaths;
}

SpriteParser::~SpriteParser(){}

//PUBLIC

void SpriteParser::update(){}

SDL_Texture* SpriteParser::next(){
    
}

//PRIVATE

void SpriteParser::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}