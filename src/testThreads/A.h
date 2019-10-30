//
// Created by axel on 30/10/19.
//

#ifndef TESTTHREADS_A_H
#define TESTTHREADS_A_H


#include <mutex>

class A {

public:
    A(int x);
    void run();
    void print();

private:
    std::mutex mu;
    int x;
};


#endif //TESTTHREADS_A_H
