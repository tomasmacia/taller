//
// Created by Tomás Macía on 21/09/2019.
//

#include "CLIArgumentParser.h"
#include <string>
#include <iostream>

using namespace std;


void CLIArgumentParser::init(int argc, const char **args) {
    this->argc = argc;
    this->argv = args;
}

string CLIArgumentParser::getPathToConfigFileName() {
    string pathToConfigFile;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (((arg == "-c") || (arg == "--config")) && (i + 1 < argc)) {
            pathToConfigFile = argv[i + 1];
        }
    }

    return pathToConfigFile;
}

string CLIArgumentParser::getDefaultLoggerLevel() {
    string defaultLoggerLevel;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (((arg == "-l") || (arg == "--logger")) && (i + 1 < argc)) {
            defaultLoggerLevel = argv[i + 1];
        }
    }

    return defaultLoggerLevel;
}