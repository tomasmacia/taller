//
// Created by axel on 9/12/19.
//

#ifndef GAME_SOUNDWRAPPER_H
#define GAME_SOUNDWRAPPER_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <string>


class SoundWrapper {

public:
    SoundWrapper(bool isMusic);

    void play();
    void load(const std::string& path);
    bool playing();
    ~SoundWrapper();

private:
    bool isMusic;
    Mix_Chunk *sound = nullptr;
    Mix_Music *music = nullptr;
};


#endif //GAME_SOUNDWRAPPER_H
