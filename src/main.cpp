#include "game.h"
#include "parser/CLIArgumentParser.h"

  
int main(int argc, const char** argv) {
    CLIArgumentParser::getInstance().init(argc, argv);

    Game::getInstance().start();

    return 0;
} 
