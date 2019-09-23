#include "DebugLogger.h"
#include "LogManager.h"

void DebugLogger::logError(std::string message){
    InfoLogger::logError(message);
};

void DebugLogger::logInfo(std::string message){
    InfoLogger::logInfo(message);
};

void DebugLogger::logDebug(std::string message){
    LogManager::writeLogFile(message, "DEBUG");
};