#include "SoundWrapper.h"
#include "GameClient.h"
#include "GameServer.h"

SDL_Renderer* _renderer = nullptr;

//CONSTRUCTOR
//=========================================================================================
SoundWrapper::SoundWrapper() {
    //Initialize

}

bool SoundWrapper::loadFromFile(std::string path){


}

SoundWrapper::~SoundWrapper() {
    free();
}

void SoundWrapper::free(){
    Mix_FreeChunk(sound);
}