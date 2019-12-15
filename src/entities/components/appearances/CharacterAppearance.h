
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "AnimatedAppearance.h"
#include "../../../XMLparser/config/characterxml.h"

class CharacterAppearance : public AnimatedAppearance {
public:
    CharacterAppearance(int w, int h, Position* position, ScreenPosition* screenPosition, State* state, CharacterXML characterConfig);

    void setConnected();
    void setDisconnected();

protected:
    void init() override;

private:
    string disconnectedSpritePath;
    string realSpritePath;
};
#endif
