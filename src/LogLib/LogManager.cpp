#include "LogManager.h"
#include "Logger.h"
#include <fstream>

Logger LogManager::loggerToBeUsed;
bool LogManager::pathHasBeenSet;
std::ofstream LogManager::file;

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
    file << message;
};

