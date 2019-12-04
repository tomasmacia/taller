//
// Created by Tomás Macía on 06/09/2019.
//

#ifndef GAME_UTILITYCONFIG_H
#define GAME_UTILITYCONFIG_H

#include <string>

using namespace std;

class UtilityConfig {
public:
    int amount;
    string standSprite;
    string beingAttacked;
    string dying;
    double knivesDropProb;
    double tubesDropProb;
};

#endif //GAME_UTILITYCONFIG_H
