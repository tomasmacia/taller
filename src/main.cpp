#include <iostream>
#include <string>
#include "parser/xmlparser.h"
#include "parser/CLIArgumentParser.h"
#include "window.h"
#include "square.h"
#include "game/Game.h"

using namespace std;

  
int main(int argc, const char** argv) {
//    string pathToConfigFile;
//
//    if (argc >= 3 && (string(argv[1]) == "-c" || string(argv[1]) == "--config")){
//        pathToConfigFile = argv[2];
//    } else {
//        cerr << "No config file specified." << endl <<
//        "USAGE: " << argv[0] << " --config path/to/config/file.xml" << endl;
//    }

    CLIArgumentParser *cliArgumentParser = CLIArgumentParser::getInstance();
    cliArgumentParser->init(argc, argv);


    Game *game = Game::getInstance();
    game->start();

    return 0;
}
