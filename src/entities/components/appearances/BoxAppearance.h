//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_BOXAPPEARANCE_H
#define GAME_BOXAPPEARANCE_H

#include "UtilityAppearance.h"
#include "../../../XMLparser/config/UtilityConfig.h"

class BoxAppearance : public UtilityAppearance {
public:
    BoxAppearance(int w, int h, ScreenPosition* screenPosition, State* state, UtilityConfig config);

protected:
    void init() override ;
};


#endif //GAME_BOXAPPEARANCE_H
