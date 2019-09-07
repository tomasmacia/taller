#include <string>
#include "Logger.h"

#ifndef ERROR_LOGGER_H_
#define ERROR_LOGGER_H_
class ErrorLogger : public Logger{
    public:
    void logError(std::string message);
    void logInfo(std::string message);
    void logDebug(std::string message);
};

#endif