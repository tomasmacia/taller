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
    if (argc >= 3 && (string(this->argv[1]) == "-c" || string(argv[1]) == "--config")){
        pathToConfigFile = argv[2];
    } else {
        cerr << "No config file specified." << endl <<
             "USAGE: " << argv[0] << " --config path/to/config/file.xml" << endl;
    }

    return pathToConfigFile;
}

string CLIArgumentParser::getDefaultLoggerLevel() {
    return "ERROR"; // TODO parsear mejor esto
}