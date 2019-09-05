#include "Logger.h"

void LogManager::setStaticLogger(Logger logger){
    loggerToBeUsed = logger;
};

void LogManager::setStaticLogPath(std::string path){
    if(LogManager::pathHasBeenSet){
        LogManager::file.close();
    };
        file.open(path);
        LogManager::pathHasBeenSet = true;
};

void LogManager::logError(std::string message){
    loggerToBeUsed.logError(message);
};

void LogManager::logInfo(std::string message){
    loggerToBeUsed.logInfo(message);
};

void LogManager::logDebug(std::string message){
    loggerToBeUsed.logDebug(message);
};

void LogManager::writeLogFile(std::string message){
    file << message.c_str;
};

void ErrorLogger::logError(std::string message){
    LogManager::writeLogFile(message);
};

void InfoLogger::logInfo(std::string message){
    LogManager::writeLogFile(message);
};

void DebugLogger::logDebug(std::string message){
    LogManager::writeLogFile(message);
};