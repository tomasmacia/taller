#include <iostream>
#include <string>
#include "parser/xmlparser.h"
#include "window.h"
#include "square.h"
#include "Game.h"

using namespace std;

// void pollEvents(Window &window,Square &square){ //HARDCODEADO
//     SDL_Event event;

//     if (SDL_PollEvent(&event)){
//         square.pollEvents(event);
//         window.pollEvents(event);
//     }
// }
  
int main(int argc, const char** argv) {
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

    Window* window = new Window("titulo",800,600);
    Square* square = new Square(100, 400, 300, 200, 0, 200, 255);

    // while (!window.isClosed()){
    //     pollEvents(window, square);
    //     square.display();
    //     window.display();
    // }

    Game game;
    game.setup();
    game.addDisplayable(square);
    game.addUpdateable(square);
    game.addDisplayable(window);
    game.addUpdateable(window);
    game.start();

    return 0;
}
