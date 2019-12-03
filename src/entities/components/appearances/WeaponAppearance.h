//
// Created Nby axelmpm on 2/12/19.
//

#ifndef GAME_WEAPONAPPEARANCE_H
#define GAME_WEAPONAPPEARANCE_H

#include "AnimatedAppearance.h"
#include "config/WeaponConfig.h"

class WeaponAppearance : public StateDrivenAppearance {
public:
    WeaponAppearance(int w, int h, ScreenPosition *screenPosition, State *state, WeaponConfig config);

    void handleCurrentState() override{}

protected:
    WeaponConfig config;

    int STAND_IMAGE_AMOUNT;
};
#endif //GAME_WEAPONAPPEARANCE_H
