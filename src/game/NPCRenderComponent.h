
#ifndef NPC_RENDER_COMPONENT_H
#define NPC_RENDER_COMPONENT_H

#include "RenderComponent.h"
#include "../parser/config/npc.h"

class NPCRenderComponent : public RenderComponent {
public:
    NPCRenderComponent(NPC *npcConfig);
    void init() override;

    int getJumpDuration();

protected:
    void handleIncomingAction() override;

private:
    NPC npcConfig;

    int STAND_IMAGE_AMOUNT = 1;
    int WALK_IMAGE_AMOUNT = 5;
    int JUMP_IMAGE_AMOUNT = 13;
    int PUNCH_IMAGE_AMOUNT = 3;
    int KICK_IMAGE_AMOUNT = 6;
    int JUMP_KICK_IMAGE_AMOUNT = 13;
    int CROUCH_IMAGE_AMOUNT = 4;
};
#endif //NPC_RENDER_COMPONENT_H