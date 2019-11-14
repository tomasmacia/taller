#include "LogLib/LogManager.h"
#include "LogLib/ErrorLogger.h"
#include "LogLib/InfoLogger.h"
#include "LogLib/DebugLogger.h"

//This main function tests the logger, the phares "this should be printed" should be printed 6 times, and you should never see "this should not"
//Creates and OVERWRITES ./test.txt
int main(int argc, char** argv) { 
    ErrorLogger* logger = new ErrorLogger();
    LogManager::setStaticLogger(logger);
    LogManager::setStaticLogPath("test.txt");

    LogManager::logError("This should be printed, error");
    LogManager::logInfo("This should not");
    LogManager::logDebug("This should not");

    InfoLogger* logger2 = new InfoLogger();
    LogManager::setStaticLogger(logger2);

    LogManager::logError("This should be printed, error");
    LogManager::logInfo("This should be printed, info");
    LogManager::logDebug("This should not");

    DebugLogger* logger3 = new DebugLogger();
    LogManager::setStaticLogger(logger3);

    LogManager::logError("This should be printed, error");
    LogManager::logInfo("This should be printed, info");
    LogManager::logDebug("This should be printed, debug");

    delete logger;
    delete logger2;
    delete logger3;
}; 