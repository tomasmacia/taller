#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

#include "game.h"
#include "events.h"
#include "Controller.h"
#include "parser/CLIArgumentParser.h"
#include "parser/config/config.h"
#include "parser/xmlparser.h"
#include "LogLib/Logger.h"
#include "LevelBuilder.h"
#include "utils/TimeUtils.h"




void Game::init() {
    //this->isRunning= false;
    this->initLogManager(CLIArgumentParser::getInstance().getDefaultLoggerLevel());
    this->initConfig();
    this->initLogManager(this->config->loggerLevel);
    this->initSDL();
    this->initController();
    this->loadHotkeys(this->config);
}

void Game::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void Game::initLogManager(string loggerLevel) {
    delete(this->logger);
    this->logger = nullptr;
    this->logger = LogManager::createLoggerFromLevel(loggerLevel);

    string currentTime = TimeUtils::getCurrentTime();
    std::replace(currentTime.begin(), currentTime.end(), ' ', '_');

    string logfilePath = "logs/log_" + currentTime + ".txt";

    LogManager::setStaticLogger(this->logger);
    LogManager::setStaticLogPath(logfilePath);

}

void Game::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LogManager::logError("Fallo SDL_Image");
        }

        int windowWidth = this->config->screenResolution.width;
        int windowHeight = this->config->screenResolution.height;

        this->window = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
    }

    if (this->window == nullptr || this->renderer == nullptr) {
        this->isRunning = false;
        LogManager::logError("SDL no pudo inicializarse");
    } else {
        this->isRunning = true;
        //SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    }

}

void Game::initController() {
    this->controller = new Controller();
}


void Game::UpdateAtras(vector<Game_Component*> vector) {
     for (auto &objeto : vector) {
        if (character->GetPosY() >= objeto->GetPosY()) {
            objeto->updateImage();
        }
    }
}


void Game::UpdateDelante(vector<Game_Component*> vector) {
     for (auto &objeto : vector) {
        if (character->GetPosY() < objeto->GetPosY()) {
            objeto->updateImage();
        }
    }
}


void Game::start() {
    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;

    LevelBuilder levelBuilder;
    this->hasNextLevel = true;


    while (isRunning && hasNextLevel) {
        this->hasNextLevel = levelBuilder.loadNext();
        this->levelFinished = false;

        Events event(this, character);

        while (isRunning && hasNextLevel && !levelFinished) {
            isRunning = !(event.keyboard_event());
            /* Limpio la pantalla */
            SDL_RenderClear(renderer);

            /* Actualizo la imagen */
            far->updateImage();

            if (middle != nullptr) {
                middle->updateImage();
            }

            floor->updateImage();

            /* Enemigos con pos y menor a pj */
            UpdateAtras(obj_escenario);

            /* cody se actualiza a lo ultimo */
            character->updateImage();
            this->levelFinished = character->inFinal();

            /* Enemigos con pos y mayor a pj */

            UpdateDelante(obj_escenario);
            /* Estoy recorriendo 2 veces el mismo vector para poner
             * cosas que estan detras de cody detras, ¿es necesario? */

            overlay->updateImage();
            /* Refresco la pantalla con nueva posicion */

            SDL_RenderPresent(renderer);

            current = 1000 / ( (Uint32) SDL_GetTicks() - fps_last);
            fps_last = (Uint32) SDL_GetTicks();
            setWindowTitleWithFPS(current);
        }
    }
}

void Game::processInput() {
    controller->processInput();
}

void Game::update() {
    for (auto &object : gameObjects) {
        object->update();
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    for (auto &object : gameObjects) {
        object->render();
    }

    SDL_RenderPresent(renderer);
}


void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   far->move();

   if (middle != nullptr) {
       middle->move();
   }

   floor->move();

   for (auto &objeto : obj_escenario) {
       objeto->move();
   }

   overlay->move();
}


void Game::setWindowTitleWithFPS(int fps){

    char szFps[128];
    sprintf(szFps, "%s: %d FPS", "Final Fight", fps);
    SDL_SetWindowTitle(window, szFps);
}

void Game::pj_in_final(){
    /* Si llegue al final de pantalla, el jugador es libre de moverse
    por toda la pantalla. Le modifico el limite vertical. */
    character->change_limits();
    //le aviso a los obj_escenario que ya no se muevan al llegar
    //cody al final de la pantalla
    for (auto &objeto : obj_escenario){
        objeto->moverse = false;
    }
}

void Game::destroyLevelObjects() {
    middleSprites.clear();
    overlaySprites.clear();
    floorSprites.clear();
    farSprites.clear();

    delete(floor);
    floor = nullptr;
    delete(middle);
    middle = nullptr;
    delete(far);
    far = nullptr;
    delete(overlay);
    overlay = nullptr;
    delete(character);
    character = nullptr;

    for (auto objeto : obj_escenario) {
        delete(objeto);
        objeto = nullptr;
    }

    obj_escenario.clear();
}

void Game::destroy() {
    destroyLevelObjects();

    delete(logger);
    logger = nullptr;

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

void Game::loadHotkeys(Config* config){
    Events::initHotkeys();
    Events::addHotkey(stringToScancode(config->bindings.ATTACK),PUNCH);
    Events::addHotkey(stringToScancode(config->bindings.CROUCH),CROUCH);
    Events::addHotkey(stringToScancode(config->bindings.DOWN),DOWN);
    Events::addHotkey(stringToScancode(config->bindings.JUMP),JUMP);
    Events::addHotkey(stringToScancode(config->bindings.LEFT),LEFT);
    Events::addHotkey(stringToScancode(config->bindings.RIGHT),RIGHT);
    Events::addHotkey(stringToScancode(config->bindings.UP),UP);
    
    Events::addHotkey(SDL_SCANCODE_ESCAPE,QUIT);
    Events::addHotkey(stringToScancode(config->bindings.JUMPKICK),JUMP_KICK);
    Events::addHotkey(stringToScancode(config->bindings.KICK),KICK);
};

SDL_Scancode Game::stringToScancode(std::string s){

    //Wellcome to hell

    if ((s == "A") or (s == "a")){
        return SDL_SCANCODE_A;
    };
    if ((s == "B") or (s == "b")){
        return SDL_SCANCODE_B;
    };
    if ((s == "C") or (s == "c")){
        return SDL_SCANCODE_C;
    };
    if ((s == "D") or (s == "d")){
        return SDL_SCANCODE_D;
    };
    if ((s == "E") or (s == "e")){
        return SDL_SCANCODE_E;
    };
    if ((s == "F") or (s == "f")){
        return SDL_SCANCODE_F;
    };
    if ((s == "G") or (s == "g")){
        return SDL_SCANCODE_G;
    };
    if ((s == "H") or (s == "h")){
        return SDL_SCANCODE_H;
    };
    if ((s == "I") or (s == "i")){
        return SDL_SCANCODE_I;
    };
    if ((s == "J") or (s == "j")){
        return SDL_SCANCODE_J;
    };
    if ((s == "K") or (s == "k")){
        return SDL_SCANCODE_K;
    };
    if ((s == "L") or (s == "l")){
        return SDL_SCANCODE_L;
    };
    if ((s == "M") or (s == "m")){
        return SDL_SCANCODE_M;
    };
    if ((s == "N") or (s == "n")){
        return SDL_SCANCODE_N;
    };
    if ((s == "O") or (s == "o")){
        return SDL_SCANCODE_O;
    };
    if ((s == "P") or (s == "p")){
        return SDL_SCANCODE_P;
    };
    if ((s == "Q") or (s == "q")){
        return SDL_SCANCODE_Q;
    };
    if ((s == "R") or (s == "r")){
        return SDL_SCANCODE_R;
    };
    if ((s == "S") or (s == "s")){
        return SDL_SCANCODE_S;
    };
    if ((s == "T") or (s == "t")){
        return SDL_SCANCODE_T;
    };
    if ((s == "U") or (s == "u")){
        return SDL_SCANCODE_U;
    };
    if ((s == "V") or (s == "v")){
        return SDL_SCANCODE_V;
    };
    if ((s == "W") or (s == "w")){
        return SDL_SCANCODE_W;
    };
    if ((s == "X") or (s == "x")){
        return SDL_SCANCODE_X;
    };
    if ((s == "Y") or (s == "y")){
        return SDL_SCANCODE_Y;
    };
    if ((s == "Z") or (s == "z")){
        return SDL_SCANCODE_Z;
    };
    if ((s == "CONTROL") or (s == "LCTRL")){
        return SDL_SCANCODE_LCTRL;
    };
    if (s == "RCTRL"){
        return SDL_SCANCODE_RCTRL;
    };
    if ((s == "SHIFT") or (s == "LSHIFT")){
        return SDL_SCANCODE_LSHIFT;
    };
    if (s == "RSHIFT"){
        return SDL_SCANCODE_RSHIFT;
    };
    if ((s == "ALT") or (s == "LALT")){
        return SDL_SCANCODE_LALT;
    };
    if (s == "SPACE"){
        return SDL_SCANCODE_SPACE;
    };
    if (s == "UP"){
        return SDL_SCANCODE_UP;
    };
    if (s == "LEFT"){
        return SDL_SCANCODE_LEFT;
    };
    if (s == "RIGHT"){
        return SDL_SCANCODE_RIGHT;
    };
    if (s == "DOWN"){
        return SDL_SCANCODE_DOWN;
    };
    if (s == "1"){
        return SDL_SCANCODE_KP_1;
    };
    if (s == "2"){
        return SDL_SCANCODE_KP_2;
    };
    if (s == "3"){
        return SDL_SCANCODE_KP_3;
    };
    if (s == "4"){
        return SDL_SCANCODE_KP_4;
    };
    if (s == "5"){
        return SDL_SCANCODE_KP_5;
    };
    if (s == "6"){
        return SDL_SCANCODE_KP_6;
    };
    if (s == "7"){
        return SDL_SCANCODE_KP_7;
    };
    if (s == "8"){
        return SDL_SCANCODE_KP_8;
    };
    if (s == "9"){
        return SDL_SCANCODE_KP_9;
    };
    if (s == "0"){
        return SDL_SCANCODE_KP_0;
    };
    if (s == "ENTER"){
        return SDL_SCANCODE_RETURN;
    };
    if ((s == "RALT") or ("ALTGR")){
        return SDL_SCANCODE_RALT;
    };
    return SDL_SCANCODE_WWW;
};