#include "DebugLogger.h"
#include "LogManager.h"

void DebugLogger::logDebug(std::string message){
    LogManager::writeLogFile(message);
};