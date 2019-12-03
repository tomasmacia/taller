//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_UTILITYAPPEARANCE_H
#define GAME_UTILITYAPPEARANCE_H

#include "../../../XMLparser/config/UtilityConfig.h"
#include "StateDrivenAppearance.h"

class UtilityAppearance : public StateDrivenAppearance {
public:
    UtilityAppearance(ScreenPosition *screenPosition, State *state, UtilityConfig config);

    void handleCurrentState() override ;

protected:
    UtilityConfig config;

    int STAND_IMAGE_AMOUNT;
    int BEING_ATTACKED_IMAGE_AMOUNT;
    int DYING_IMAGE_AMOUNT;
};


#endif //GAME_UTILITYAPPEARANCE_H
