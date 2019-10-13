//
// Created by Tomás Macía on 09/10/2019.
//

#ifndef GAME_PARALLAX_H
#define GAME_PARALLAX_H


#include "GameObject.h"
#include <vector>
#include "Background.h"

class Parallax : public GameObject {
public:
    Parallax();
    ~Parallax() override {
        destroy();
    };
    void update() override;
    void render() override;

    void addNewBackground(Background *background);

private:
    std::vector<Background*> backgrounds;

    void destroy();
};


#endif //GAME_PARALLAX_H
