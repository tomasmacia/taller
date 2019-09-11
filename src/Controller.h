#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

    private:

    static bool up;
    static bool down ;
    static bool left;
    static bool right;

    public:
    static void reset();
    static void pressUp();
    static void pressDown();
    static void pressLeft();
    static void pressRight();
    static bool leftIsPressed();
    static bool rightIsPressed();
    static bool downIsPressed();
    static bool upIsPressed();
    
};


#endif