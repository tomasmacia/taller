#include "InfoLogger.h"
#include "LogManager.h"

void InfoLogger::logError(std::string message){
    ErrorLogger::logError(message);
};

void InfoLogger::logInfo(std::string message){
    LogManager::writeLogFile(message);
};

void InfoLogger::logDebug(std::string message){
    ErrorLogger::logDebug(message);
};