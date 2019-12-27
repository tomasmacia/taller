//
// Created by axelmpm on 3/12/19.
//

#ifndef GAME_TUBEAPPEARANCE_H
#define GAME_TUBEAPPEARANCE_H

#include "WeaponAppearance.h"
#include "../../../XMLparser/config/WeaponConfig.h"

class TubeAppearance : public WeaponAppearance {
public:
    TubeAppearance(int w, int h, ScreenPosition* screenPosition, State* state, WeaponConfig config);

    ~TubeAppearance() override = default;

protected:
    void init() override ;
};


#endif //GAME_TUBEAPPEARANCE_H
