//
// Created by axelmpm on 2/12/19.
//

#include "WeaponAppearance.h"

WeaponAppearance::WeaponAppearance(int w, int h, ScreenPosition *screenPosition, State *state, WeaponConfig config) :
                                    StateDrivenAppearance(screenPosition,state){
    this->config = config;
}