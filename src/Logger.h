/*
 * Logger.h
 * 
 * Created on: Sep 03, 2019
 *  Author: Franco R.
 */

#include <string>
#include <fstream>

#ifndef LOGGER_H_
#define LOGGER_H_

class Logger{

    public:
    /**
    * Logs the recieved message as an Error. This type of logs gets printed in all loggers
    */
    void logError(std::string message);

    /**
     * Logs the recieved message as Info. This type of logs gets printed in loggers INFO and DEBUG
     */
    void logInfo(std::string message);

    /**
     * Logs the recieved message as a Debug message. This type of logs gets printed in DEBUG logger only
     */
    void logDebug(std::string message);
};

class ErrorLogger : public Logger{
    void logError(std::string message);
    void logInfo(std::string message);
    void logDebug(std::string message);
};

class InfoLogger : public ErrorLogger{
    void logError(std::string message);
    void logInfo(std::string message);
    void logDebug(std::string message);
};

class DebugLogger : public InfoLogger{
    void logError(std::string message);
    void logInfo(std::string message);
    void logDebug(std::string message);
};

/*
* Allows user to log to a determined file. Can be used static or instantiated
*
* Default mode is ERROR
*/
class LogManager{
    private:
        static Logger loggerToBeUsed;
        static bool pathHasBeenSet;
        static std::ofstream file;

    public:

        /**
        * Sets the logger to be used through the rest of the execution
        * Can be changed in runtime
        */
        void static setStaticLogger(Logger logger);

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
        void static writeLogFile(std::string message);
};


#endif /*LOGGER_H_*/