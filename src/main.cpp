#include <iostream>
#include <string>
#include "parser/xmlparser.h"
using namespace std; 

int main(int argc, char** argv) { 
    cout << "Hello World 1.0" << "\n";

    if (argc >= 3 && (string(argv[1]) == "-c" || string(argv[1]) == "--config")){
        string pathToFile = argv[2];
        XMLParser parser;
        Config config = parser.parse(pathToFile);
        cout << "There are " << config.gameplay.levels.size() << " levels in the game" << "\n";
        cout << "Logger level set in " << config.loggerLevel << "\n";
    } else {
        cerr << "USAGE: " << argv[0] << " --config path/to/config/file.xml" << "\n";
    }
  
    return 0; 
} 
