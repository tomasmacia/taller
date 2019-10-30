#include <iostream>
#include <thread>
#include <mutex>

#include "A.h"

using namespace std;


int main() {

    A* a = new A(0);
    A* b = new A(1);

    std::thread t1(&A::run,a);
    std::thread t2(&A::run,b);

    t1.join();
    t2.join();



    return 0;
}