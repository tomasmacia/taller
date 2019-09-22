
#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include <string>
#include "Logger.h"

/*
* Allows user to log to a determined file. Designed to use in a global context
*
*/
class LogManager{
    private:
        static Logger *loggerToBeUsed;
        static bool pathHasBeenSet;
        static std::ofstream file;

        static std::string getCurrentTime();

    public:

        /**
        * Sets the logger to be used through the rest of the execution
        * Can be changed in runtime
        */
        void static setStaticLogger(Logger* logger);

        /**
         * Sets the name of the file to be written with the log information
         * 
         * @param path MUST include extention, example: "log.txt"
         */
        void static setStaticLogPath(std::string path);

        /**
         * Logs the recieved message as an Error. This type of logs gets printed in all loggers
         */
        void static logError(std::string message);

        /**
         * Logs the recieved message as Info. This type of logs gets printed in loggers INFO and DEBUG
         */
        void static logInfo(std::string message);

        /**
         * Logs the recieved message as a Debug message. This type of logs gets printed in DEBUG logger only
         */
        void static logDebug(std::string message);

        /**
         * Forces to write the message in the log file
         */
        void static writeLogFile(std::string message, std::string level);
};

#endif