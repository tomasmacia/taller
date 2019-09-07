/*
 * Logger.h
 * 
 * Created on: Sep 03, 2019
 *  Author: Franco R.
 */

#include <string>

#ifndef LOGGER_H_
#define LOGGER_H_

class Logger{

    public:
    /**
    * Logs the recieved message as an Error. This type of logs gets printed in all loggers
    */
    virtual void logError(std::string message);

    /**
     * Logs the recieved message as Info. This type of logs gets printed in loggers INFO and DEBUG
     */
    virtual void logInfo(std::string message);

    /**
     * Logs the recieved message as a Debug message. This type of logs gets printed in DEBUG logger only
     */
    virtual void logDebug(std::string message);
};

#endif /*LOGGER_H_*/