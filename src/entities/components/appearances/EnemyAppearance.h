
#ifndef NPC_RENDER_COMPONENT_H
#define NPC_RENDER_COMPONENT_H

#include "AnimatedAppearance.h"
#include "../../../XMLparser/config/npc.h"

class EnemyAppearance : public AnimatedAppearance {
public:
    EnemyAppearance(int w, int h, ScreenPosition* screenPosition, State* state, NPC npcConfig);

    ~EnemyAppearance() override = default;

protected:
    void init() override ;
};
#endif //NPC_RENDER_COMPONENT_H
