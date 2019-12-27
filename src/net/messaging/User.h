//
// Created by axelmpm on 13/11/19.
//

#ifndef GAME_USER_H
#define GAME_USER_H

#include <string>
using namespace std;

class User {

public:
    User(string name,string color){
        this->name = name;
        this->color = color;
    }

    string name;
    string color;
};


#endif //GAME_USER_H
