using namespace std; 

#include <iostream> 
#include "window.h"
  
int main(int argc, char** argv) { 

    Window window("titulo",1000,1000);

    while (!window.isClosed()){
        window.poolEvents();
    }

    return 0; 
} 