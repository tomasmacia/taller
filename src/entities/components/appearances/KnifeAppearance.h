//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_KNIFEAPPEARANCE_H
#define GAME_KNIFEAPPEARANCE_H

#include "WeaponAppearance.h"
#include "../../../XMLparser/config/WeaponConfig.h"

class KnifeAppearance : public WeaponAppearance {
public:
    KnifeAppearance(int w, int h, ScreenPosition* screenPosition, State* state, WeaponConfig config);

protected:
    void init() override ;
};


#endif //GAME_KNIFEAPPEARANCE_H
