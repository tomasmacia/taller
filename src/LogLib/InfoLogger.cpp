#include "InfoLogger.h"
#include "LogManager.h"

void InfoLogger::logInfo(std::string message){
    LogManager::writeLogFile(message);
};