//
// Created by Tomás Macía on 11/10/2019.
//

#ifndef GAME_BACKGROUND_H
#define GAME_BACKGROUND_H

#include "GameObject.h"

class Background : public GameObject {
public:
    Background(const char* textureFile, int x, int y);
    Background();
    ~Background() override {
        destroy();
    }
    void update() override;
    void render() override;

private:
    void destroy();
};


#endif //GAME_BACKGROUND_H
