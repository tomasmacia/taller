#include <iostream> 
#include "Logger.h"
using namespace std; 
  

void test(){
    ErrorLogger logger;
    LogManager::setStaticLogger(logger);
    LogManager::setStaticLogPath("test.txt");

    LogManager::logError("Esto Deberia imprimirse");
    LogManager::logInfo("Esto no");
    LogManager::logDebug("Esto no");

    InfoLogger logger2;
    LogManager::setStaticLogger(logger2);

    LogManager::logError("Esto Deberia imprimirse");
    LogManager::logInfo("Esto Deberia imprimirse");
    LogManager::logDebug("Esto no");

    DebugLogger logger3;
    LogManager::setStaticLogger(logger3);
    LogManager::setStaticLogPath("test.txt");

    LogManager::logError("Esto Deberia imprimirse");
    LogManager::logInfo("Esto Deberia imprimirse");
    LogManager::logDebug("Esto Deberia imprimirse");

};

int main(int argc, char** argv) { 
    cout << "Hello World 1.0" << "\n";
    test();
    return 0; 
} 
