//
// Created by Tomás Macía on 02/10/2019.
//

#include "TimeUtils.h"
#include <string>
#include <ctime>

std::string TimeUtils::getCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}