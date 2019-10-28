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
}

int main(int argc, const char** argv) {

    CLIArgumentParser::getInstance().init(argc, argv);

    Logger* logger = initLogger(CLIArgumentParser::getInstance().getDefaultLoggerLevel());
    LogManager::logDebug("inicializado LogManager");

    Mode mode = CLIArgumentParser::getInstance().getMode();

    if (mode == SERVER){
        GameServer::getInstance().start();
    }

    if (mode == CLIENT){
        GameCliente::getInstance().start();
    }

    else{
        LogManager::logError("modo de juego invalido");
    }

    delete(logger);

    return 0;
}

