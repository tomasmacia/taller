//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_CLIARGUMENTPARSER_H
#define GAME_CLIARGUMENTPARSER_H

#include <string>

using namespace std;


class CLIArgumentParser {
public:
    static CLIArgumentParser& getInstance() {
        static CLIArgumentParser instance; // Guaranteed to be destroyed.
                                           // Instantiated on first use.
        return instance;
    }

    void init(int argc, const char* args[]);

    string getPathToConfigFileName();
    string getDefaultLoggerLevel();
    string getModeType();
    string getServerAddress();
    string getServerPort();
    string getPathToUserCredentialsFileName();


    CLIArgumentParser(CLIArgumentParser const&) = delete;
    void operator=(CLIArgumentParser const&) = delete;

private:
    CLIArgumentParser() {};
    ~CLIArgumentParser() {};


    string getParamHelper(string, string);
    int argc;
    const char** argv;
};


#endif //GAME_CLIARGUMENTPARSER_H