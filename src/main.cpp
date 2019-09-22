using namespace std; 

#include <iostream> 
#include "game.h"

#include <string>
#include "parser/xmlparser.h"
#include "parser/CLIArgumentParser.h"

  
int main(int argc, const char** argv) {
    CLIArgumentParser *cliArgumentParser = CLIArgumentParser::getInstance();
    cliArgumentParser->init(argc, argv);

    Game* game = Game::getInstance();
    game->start();

    return 0;
} 
