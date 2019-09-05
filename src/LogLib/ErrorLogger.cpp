#include "ErrorLogger.h"
#include "LogManager.h"

void ErrorLogger::logError(std::string message){
    LogManager::writeLogFile(message);
};
