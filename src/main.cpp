#include <iostream> 
#include "LogLib/LogManager.h"
#include "LogLib/ErrorLogger.h"
#include "LogLib/InfoLogger.h"
#include "LogLib/DebugLogger.h"

using namespace std; 
  

void test(){
    ErrorLogger* logger = new ErrorLogger();
    LogManager::setStaticLogger(logger);
    LogManager::setStaticLogPath("test.txt");

    LogManager::logError("Esto Deberia imprimirse");
    LogManager::logInfo("Esto no");
    LogManager::logDebug("Esto no");

    InfoLogger* logger2 = new InfoLogger();
    LogManager::setStaticLogger(logger2);

    LogManager::logError("Esto Deberia imprimirse");
    LogManager::logInfo("Esto Deberia imprimirse");
    LogManager::logDebug("Esto no");

    DebugLogger* logger3 = new DebugLogger();
    LogManager::setStaticLogger(logger3);

    LogManager::logError("Esto Deberia imprimirse");
    LogManager::logInfo("Esto Deberia imprimirse");
    LogManager::logDebug("Esto Deberia imprimirse");

    delete logger;
    delete logger2;
    delete logger3;
};

int main(int argc, char** argv) { 
    cout << "Hello World 1.0" << "\n";
    test();
    return 0; 
} 
