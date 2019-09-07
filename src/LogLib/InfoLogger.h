#ifndef INFO_LOGGER_H_
#define INFO_LOGGER_H_

#include <string>
#include "ErrorLogger.h"

class InfoLogger : public ErrorLogger{
    public:
    void logError(std::string message);
    void logInfo(std::string message);
    void logDebug(std::string message);
};

#endif