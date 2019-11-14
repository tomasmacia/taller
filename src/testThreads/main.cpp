#include <iostream>
#include <thread>
#include <mutex>

#include "A.h"

using namespace std;


int main() {

    A* a = new A();

    std::thread t1(&A::run1,a);
    std::thread t2(&A::run2,a);

    t1.join();
    t2.join();

    return 0;
}