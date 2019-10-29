#include "game/Game.h"
#include "parser/CLIArgumentParser.h"
#include "game/LoggerMenu.h"


int main(int argc, const char** argv) {
    CLIArgumentParser::getInstance().init(argc, argv);
    LoggerMenu* login = new LoggerMenu();
    
    if(login->open()){
        Game::getInstance().start();
    }

    return 0;
}
