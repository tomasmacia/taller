//
// Created by axel on 24/11/19.
//

#ifndef GAME_SENDABLEGENERATOR_H
#define GAME_SENDABLEGENERATOR_H


#include "../../net/messaging/Sendable.h"
#include "Position.h"

class SendableGenerator {

public:
    SendableGenerator(Screen* screen);

    void setPosition(Position* position){
        _position = position;
    }

    void setSound(Sound* sound){
        _sound = sound;
    }

    Sendable* generateSendable();

private:
    Screen* _screen = nullptr;
    Position* _position = nullptr;
    Sound* _sound = nullptr;

};


#endif //GAME_SENDABLEGENERATOR_H
