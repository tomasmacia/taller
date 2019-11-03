#include <algorithm>
#include "../utils/TimeUtils.h"
#include "../parser/CLIArgumentParser.h"
#include "../LogLib/LogManager.h"
#include "GameServer.h"
#include "GameClient.h"
#include "Mode.h"

using namespace std;

Logger* initLogger(string loggerLevel){
    Logger* logger = LogManager::createLoggerFromLevel(loggerLevel);

    string currentTime = TimeUtils::getCurrentTime();
    std::replace(currentTime.begin(), currentTime.end(), ' ', '_');

    string logfilePath = "logs/log_" + currentTime + ".txt";

    LogManager::setStaticLogger(logger);
    LogManager::setStaticLogPath(logfilePath);
    return logger;
}

Mode getModeFromCommandLine(){
    Mode mode = CLIENT;
    string commandLineMode = CLIArgumentParser::getInstance().getModeType();
    if ((commandLineMode == "client") || (commandLineMode == "Client") || (commandLineMode == "CLIENT")){
        LogManager::logInfo("Client mode detected in command line");
    } else {
        if ((commandLineMode == "server") || (commandLineMode == "Server") || (commandLineMode == "SERVER")){
            mode = SERVER;
            LogManager::logInfo("Server mode detected in command line");
        } else {
            LogManager::logError("Incomprehensible mode in command line, going to client mode");
        }
    }
    return mode;
}

int main(int argc, const char** argv) {

    CLIArgumentParser::getInstance().init(argc, argv);

    Logger* logger = initLogger(CLIArgumentParser::getInstance().getDefaultLoggerLevel());
    LogManager::logDebug("inicializado LogManager");

    Mode mode = getModeFromCommandLine();

    if (mode == SERVER){
        GameServer::getInstance().start();
    }

    if (mode == CLIENT){
        GameClient::getInstance().start();
    }

    delete logger;

    return 0;
}