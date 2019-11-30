
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "StateDrivenAppearance.h"
#include "../../../XMLparser/config/characterxml.h"

class CharacterAppearance : public StateDrivenAppearance {
public:
    CharacterAppearance(int w, int h, Position* position, ScreenPosition* screenPosition, State* state, const CharacterXML& characterConfig);

    void setConnected();
    void setDisconnected();

protected:
    void init() override;
    void handleCurrentState() override;

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
