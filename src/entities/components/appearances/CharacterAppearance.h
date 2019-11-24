
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "MobileAppearance.h"
#include "../../../XMLparser/config/characterxml.h"

class CharacterAppearance : public MobileAppearance {
public:
    CharacterAppearance(Entity* camera, CharacterXML characterConfig);
    void init() override;

    int getJumpDuration() override;

    void setConnected();
    void setDisconnected();

protected:
    void handleIncomingAction() override;

private:
    CharacterXML characterConfig;
    string disconnectedSpritePath;
    string realSpritePath;

    int STAND_IMAGE_AMOUNT = 1;
    int WALK_IMAGE_AMOUNT = 9;
    int JUMP_IMAGE_AMOUNT = 13;
    int PUNCH_IMAGE_AMOUNT = 3;
    int KICK_IMAGE_AMOUNT = 6;
    int JUMP_KICK_IMAGE_AMOUNT = 13;
    int CROUCH_IMAGE_AMOUNT = 4;
};
#endif
