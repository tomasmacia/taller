#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <zconf.h>
#include "../sound/SoundWrapper.h"


int main(int argc, const char** argv) {

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }


    SoundWrapper *soundWrapperMusician = new SoundWrapper(true);
    SoundWrapper *soundWrapper1 = new SoundWrapper(false);
    SoundWrapper *soundWrapper2 = new SoundWrapper(false);
    SoundWrapper *soundWrapper3 = new SoundWrapper(false);
    SoundWrapper *soundWrapper4 = new SoundWrapper(false);
    SoundWrapper *soundWrapper5 = new SoundWrapper(false);


    soundWrapperMusician->load("resources/sfx/music/soundtrack.wav");
    soundWrapper1->load("resources/sfx/boss/death.wav");
    soundWrapper2->load("resources/sfx/npcs/death.wav");
    soundWrapper3->load("resources/sfx/players/great.wav");
    soundWrapper4->load("resources/sfx/players/hit.wav");
    soundWrapper5->load("resources/sfx/players/great.wav");

    soundWrapperMusician->play();

    while (soundWrapperMusician->playing()){

        usleep(2000000);
        //soundWrapper1->play();
        //soundWrapper2->play();
        soundWrapper3->play();
        usleep(2000000);
        //soundWrapper4->play();
        soundWrapper5->play();

    }

    return 0;
}






/*
Mix_Music *music = NULL;

Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;


//  INIT
if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
{
return false;
}

if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
{
return false;
}

//Load
music = Mix_LoadMUS( "beat.wav" );

scratch = Mix_LoadWAV( "src/game/scratch.wav" );
high = Mix_LoadWAV( "src/game/high.wav" );
med = Mix_LoadWAV( "medium.wav" );
low = Mix_LoadWAV( "low.wav" );

if( Mix_PlayChannel( -1, high, 0 ) == -1 )
{
return 1;
}

if( scratch == NULL )
{
return false;
}

Mix_Volume(-1, 100);

if( Mix_PlayChannel( -1, scratch, 0 ) == -1 )
{
return 1;
}

//Free the sound effects
Mix_FreeChunk( scratch );
Mix_FreeChunk( high );
Mix_FreeChunk( med );
Mix_FreeChunk( low );

//Free the music
Mix_FreeMusic( music );

//Quit SDL_mixer
Mix_CloseAudio();

//Quit SDL
SDL_Quit();


*/

















































/*
#include <algorithm>
#include "../time/TimeUtils.h"
#include "../CLIAparser/CLIArgumentParser.h"
#include "../logger/LogManager.h"
#include "LoggerMenu.h"
#include "GameServer.h"
#include "GameClient.h"
#include "../enumerates/Mode.h"

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

Mode getModeFromCommandLine(int argc, const char** argv){
    Mode mode = CLIENT;
    string commandLineMode;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (((arg == "-m") || (arg == "--mode")) && (i + 1 < argc)) {
            commandLineMode = argv[i + 1];
            if ((commandLineMode == "client") || (commandLineMode == "Client") || (commandLineMode == "CLIENT")){
                LogManager::logInfo("[CLI]: Client mode detected in command line");
            } else {
                if ((commandLineMode == "server") || (commandLineMode == "Server") || (commandLineMode == "SERVER")){
                    mode = SERVER;
                    LogManager::logInfo("[CLI]: Server mode detected in command line");
                } else {
                    LogManager::logError("[CLI]: Incomprehensible mode in command line, going to client mode");
                }
            }
        }
    }
    return mode;
}

int main(int argc, const char** argv) {

    CLIArgumentParser::getInstance().init(argc, argv);

    Logger* logger = initLogger(CLIArgumentParser::getInstance().getDefaultLoggerLevel());
    LogManager::logDebug("[INIT]: inicializado LogManager");

    Mode mode = getModeFromCommandLine(argc, argv);

    if (mode == SERVER){
        GameServer::getInstance().start();
    }

    if (mode == CLIENT){
        GameClient::getInstance().start();
    }
    return 0;
}
 */