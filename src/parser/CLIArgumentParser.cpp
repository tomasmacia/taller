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
    return getParamHelper("-c", "--config");
}

string CLIArgumentParser::getDefaultLoggerLevel() {
    return getParamHelper("-l", "--logger");
}

string CLIArgumentParser::getModeType() {
    return getParamHelper("-m", "--mode");
}

string CLIArgumentParser::getServerAddress() {
    return getParamHelper("-a", "--address");
}

string CLIArgumentParser::getServerPort() {
    return getParamHelper("-p", "--port");
}

string CLIArgumentParser::getParamHelper(string shortCommand, string descriptiveCommand) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (((arg == shortCommand) || (arg == descriptiveCommand)) && (i + 1 < argc)) {
            return argv[i + 1];
        }
    }

    return "";
}