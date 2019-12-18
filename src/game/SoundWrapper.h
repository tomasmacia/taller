
#ifndef GAME_SOUNDWRAPPER_H
#define GAME_SOUNDWRAPPER_H

#include <string>
#include <vector>
#include <SDL2/SDL_mixer.h>


class SoundWrapper {
public:
    SoundWrapper();
    ~SoundWrapper();

    //API
    //===============================
    bool loadFromFile(std::string path); 


private:

    //DESTROY
    //===============================
    void free();

    //ATRIBUTES
    //===============================
    Mix_Chunk* sound = nullptr;

};

#endif //GAME_SOUNDWRAPPER_H
