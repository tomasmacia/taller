#ifndef GAME_LEVELLIMITS_H
#define GAME_LEVELLIMITS_H

#include "ECS.h"
#include "CameraComponent.h"


class LevelLimits : public Component{
public:
    LevelLimits(int windowWidth, int windowHeigh, int levelWidth,
                 CameraComponent* camera);

    void update() override;

    int generateValidInScreenX();
    int generateValidInScreenY();
    bool newPositionOutOfRange(int x, int y);

private:
    int _windowHeight, _windowWidth, _levelWidth;

    int _minY, _maxY, _minX, _maxX;
    int _rangeOfMovementY, _offsetY;
    int _toleranceX, _toleranceY;

    CameraComponent* _camera = nullptr;
};


#endif //GAME_LEVELLIMITS_H
