
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "MobileRenderComponent.h"
#include "../parser/config/characterxml.h"

class CharacterRenderComponent : public MobileRenderComponent {
public:
    CharacterRenderComponent(Entity* camera, CharacterXML characterConfig);
    void init() override;

    int getJumpDuration() override;

protected:
    void handleIncomingAction() override;

private:
    CharacterXML characterConfig;

    int STAND_IMAGE_AMOUNT = 1;
    int WALK_IMAGE_AMOUNT = 9;
    int JUMP_IMAGE_AMOUNT = 13;
    int PUNCH_IMAGE_AMOUNT = 3;
    int KICK_IMAGE_AMOUNT = 6;
    int JUMP_KICK_IMAGE_AMOUNT = 13;
    int CROUCH_IMAGE_AMOUNT = 4;
};
#endif
