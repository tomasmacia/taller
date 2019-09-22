#include "LogManager.h"
#include "Logger.h"
#include <fstream>

Logger* LogManager::loggerToBeUsed;
bool LogManager::pathHasBeenSet;
std::ofstream LogManager::file;

void LogManager::setStaticLogger(Logger* logger){
    loggerToBeUsed = logger;
};

void LogManager::setStaticLogPath(std::string path){
    if(LogManager::pathHasBeenSet){
        LogManager::file.close();
    }

    file.open(path);
    LogManager::pathHasBeenSet = true;
};

void LogManager::logError(std::string message){
    loggerToBeUsed->logError(message);
};

void LogManager::logInfo(std::string message){
    loggerToBeUsed->logInfo(message);
};

void LogManager::logDebug(std::string message){
    loggerToBeUsed->logDebug(message);
};

void LogManager::writeLogFile(std::string message, std::string level){
    file << getCurrentTime() + " [" + level + "] : " + message << std::endl;
};

std::string LogManager::getCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}

