//
// Created by axel on 24/11/19.
//

#ifndef GAME_SOUNDABLE_H
#define GAME_SOUNDABLE_H

#include <string>
#include <map>
#include "../../sound/SoundWrapper.h"


using namespace std;

class Soundable {

public:
    Soundable(string soundPath, bool isMusic);

    void play(std::map<string,SoundWrapper*>* loadedSoundsMap);

    string getPath();

    bool getBoolMusic();

    bool _isMusic;
    string _soundPath;



};


#endif //GAME_SOUNDABLE_H
