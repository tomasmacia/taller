//
// Created by Tomás Macía on 05/09/2019.
//

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include <string>

using namespace std;

class Level {
public:
    vector<string> floor;
    vector<string> middle;
    vector<string> far;
    vector<string> overlay;
};

#endif //GAME_LEVEL_H
