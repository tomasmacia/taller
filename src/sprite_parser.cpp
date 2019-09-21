#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite_parser.h"
#include "sprite.h"

//CONSTRUCTOR & DESTRUCTOR
SpriteParser::SpriteParser(std::vector <Sprite*>* sprites){
    _sprites = sprites;
    _totalSprites = _sprites->size();
    _currentSpriteNumber = 0;
}

//PUBLIC
Sprite* SpriteParser::next(){
    _currentSpriteNumber++;
    _currentSpriteNumber = _currentSpriteNumber % _totalSprites;    //para que vuelva a empezar
    Sprite* currentSprite = _sprites->at(_currentSpriteNumber);
    return currentSprite;
}

//PRIVATE
void SpriteParser::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}