//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_BARRELAPPEARANCE_H
#define GAME_BARRELAPPEARANCE_H

#include "UtilityAppearance.h"
#include "../../../XMLparser/config/UtilityConfig.h"

class BarrelAppearance : public UtilityAppearance {
public:
    BarrelAppearance(int w, int h, ScreenPosition* screenPosition, State* state, UtilityConfig config);

    ~BarrelAppearance() override = default;

protected:
    void init() override ;
};


#endif //GAME_BARRELAPPEARANCE_H
