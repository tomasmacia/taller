#ifndef GAME_INPUTCOMPONENT_H
#define GAME_INPUTCOMPONENT_H

#include "Component.h"
#include "Controller.h"
#include "character.h"

class InputComponent : public Component {

private:
    std::vector<Action> _actions;
    Controller* _controller = nullptr;
    Character* _character = nullptr;

public:
    InputComponent(Controller* controller, Character* character);
    ~InputComponent();

    void update() override;
    void render() override{}

protected:
    void switchAction(Action action){}

private:
    bool ifXOutOfRange();
    bool ifYOutOfRange();
};

#endif //GAME_INPUTCOMPONENT_H