using namespace std; 

#include <iostream> 
#include "game.h"

#include <string>
#include "parser/xmlparser.h"
#include "parser/CLIArgumentParser.h"

  
int main(int argc, const char** argv) {
    string pathToFile;

    CLIArgumentParser *cliArgumentParser = CLIArgumentParser::getInstance();
    cliArgumentParser->init(argc, argv);

    if (argc >= 3 && (string(argv[1]) == "-c" || string(argv[1]) == "--config")){
        pathToFile = argv[2];
    } else {
        cerr << "No config file specified." << endl <<
        "USAGE: " << argv[0] << " --config path/to/config/file.xml" << endl;
    }

    XMLParser parser;
    Config config = parser.parse(pathToFile);
    cout << "There are " << config.gameplay.levels.size() << " levels in the game" << endl;
    cout << "Logger level set in " << config.loggerLevel << endl;


   Game* game = new Game (800,600);

    return 0;
} 
