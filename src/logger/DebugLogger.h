#ifndef DEBUG_LOGGER_H_
#define DEBUG_LOGGER_H_

#include <string>
#include "InfoLogger.h"

class DebugLogger : public InfoLogger{
    public:
    void logError(std::string message);
    void logInfo(std::string message);
    void logDebug(std::string message);
};

#endif