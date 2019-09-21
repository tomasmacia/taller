//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_CLIARGUMENTPARSER_H
#define GAME_CLIARGUMENTPARSER_H

#include <string>

using namespace std;


class CLIArgumentParser {
public:
    static CLIArgumentParser* getInstance();
    void init(int argc, const char* args[]);

    string getPathToConfigFileName();
    string getDefaultLoggerLevel();

private:
    static CLIArgumentParser* instance;
    CLIArgumentParser() {};
    ~CLIArgumentParser() {};

    int argc;
    const char** argv;
};


#endif //GAME_CLIARGUMENTPARSER_H
