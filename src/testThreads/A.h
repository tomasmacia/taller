//
// Created by axel on 30/10/19.
//

#ifndef TESTTHREADS_A_H
#define TESTTHREADS_A_H


#include <mutex>
#include <iostream>
using namespace std;

class A {

public:
    void run1();
    void run2();
    void print(int x);

private:
    std::mutex mu;
};


#endif //TESTTHREADS_A_H
