//
// Created by axel on 30/10/19.
//

#include <iostream>
#include "A.h"

using namespace std;

void A::run1() {

    while(true){
        print(1);
    }
}

void A::run2() {

    while(true){
        print(2);
    }
}


void A::print(int x) {
    mu.lock();
    cout<<"value: "<<x<<endl;
    mu.unlock();
}