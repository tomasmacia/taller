#ifndef GAME_PHYSICSCOMPONENT_H
#define GAME_PHYSICSCOMPONENT_H


class PhysicsComponent {

private:

    int _x;
    int _y;
    int _velocity;

public:
    PhysicsComponent(int x, int y);
    ~PhysicsComponent();

    void setVelocity(int velocity);
};

#endif //GAME_PHYSICSCOMPONENT_H