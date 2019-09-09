#include <iostream>
#include <string>
#include "parser/xmlparser.h"
using namespace std; 

int main(int argc, char** argv) {
    string pathToFile;

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
  
    return 0; 
} 
