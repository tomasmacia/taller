//
// Created by axel on 30/10/19.
//

#include <iostream>
#include "A.h"

using namespace std;

A::A(int x) {
    this->x = x;
}

void A::run() {

    while(true){
        print();
    }
}

void A::print() {
    mu.lock();
    cout<<"value: "<<x<<endl;
    mu.unlock();
}