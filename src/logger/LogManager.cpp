#include "LogManager.h"
#include "Logger.h"
#include "DebugLogger.h"
#include "../utils/TimeUtils.h"
#include <fstream>

Logger* LogManager::loggerToBeUsed;
bool LogManager::pathHasBeenSet;
std::ofstream LogManager::file;

void LogManager::setStaticLogger(Logger* logger){
    loggerToBeUsed = logger;
};

void LogManager::setStaticLogPath(std::string path) {
    if (LogManager::pathHasBeenSet) {
        LogManager::file.close();
        file.open(path, std::fstream::app);
    } else {
        file.open(path);
        file << "//****************** LOGGER ******************//" << std::endl;
        LogManager::pathHasBeenSet = true;
    }
};

Logger* LogManager::createLoggerFromLevel(const std::string& level) {
    Logger* logger;
    if (level == "DEBUG") {
        logger = new DebugLogger();
    } else if (level == "INFO") {
        logger = new InfoLogger();
    } else {
        logger = new ErrorLogger();
    }

    return logger;
}

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
    file << TimeUtils::getCurrentTime() + " [" + level + "] : " + message << std::endl;
};

