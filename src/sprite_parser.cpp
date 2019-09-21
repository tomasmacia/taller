#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite_parser.h"

//CONSTRUCTOR & DESTRUCTOR
SpriteParser::SpriteParser(std::vector <std::string>& spritePaths){
    _spritePaths = spritePaths;
    _totalSprites = _spritePaths.size();
    _currentSpriteNumber = 0;
}

//PUBLIC
std::string SpriteParser::next(){
    _currentSpriteNumber++;
    _currentSpriteNumber = _currentSpriteNumber % _totalSprites;    //para que vuelva a empezar
    std::string currentImagePath = _spritePaths[_currentSpriteNumber];
    return currentImagePath;
}

//PRIVATE
void SpriteParser::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}