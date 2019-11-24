#include "ErrorLogger.h"
#include "LogManager.h"

void ErrorLogger::logError(std::string message){
    LogManager::writeLogFile(message, "ERROR");
};

void ErrorLogger::logInfo(std::string message){
    Logger::logInfo(message);
};

void ErrorLogger::logDebug(std::string message){
    Logger::logDebug(message);
};
