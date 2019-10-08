#ifndef GAME_H_
#define GAME_H_

#include "background.h"
#include "object.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "GameObject.h"
#include "Controller.h"
#include "LogLib/LogManager.h"
#include "parser/config/config.h"
#include "game_component.h"
#include "character.h"

class Game {
public:
    static Game& getInstance() {
        static Game instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    // gameloop
    void start();

    class Character* character;
    Background *far, *middle;
    Background *floor, *overlay;
    void move_all();
    void pj_in_final();

    bool isRunning = true; // false
    bool levelFinished = false;

    void addGameObject(GameObject *gameObject) {
        gameObjects.push_back(gameObject);
    }

    void addGameComponent(Game_Component* gameComponent) {
        obj_escenario.push_back(gameComponent);
    }

    // ****** MOMENTANEOOOO !!!! *****

    void setFloorSprites(vector<std::string> floor) {
        floorSprites.clear();
        floorSprites = floor;
    }

    void setMiddleSprites(vector<std::string> middle) {
        middleSprites.clear();
        middleSprites = middle;
    }

    void setFarSprites(vector<std::string> far) {
        farSprites.clear();
        farSprites = far;
    }

    void setOverlaySprites(vector<std::string> overlay) {
        overlaySprites.clear();
        overlaySprites = overlay;
    }

    void setCharacter(Character* pj) {
        character = pj;
    }

    void setFarBackground(Background *farBackground) {
        far = farBackground;
    }

    void setMiddleBackground(Background *middleBackground) {
        middle = middleBackground;
    }

    void setFloorBackground(Background *floorBackground) {
        floor = floorBackground;
    }

    void setOverlayBackground(Background *overlayBackground) {
        overlay = overlayBackground;
    }

    std::vector<Game_Component*> getGameComponents() {
        return obj_escenario;
    }

    std::vector <string> floorSprites;
    std::vector <string> middleSprites;
    std::vector <string> farSprites;
    std::vector <string> overlaySprites;

    void destroyLevelObjects();


    // *******************************

    // wrapper getters
    Config* getConfig() {
        return config;
    }

    Controller* getController() {
        return controller;
    }

    SDL_Window* getWindow() {
        return window;
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

private:
    Game() {
        init();
    }

    ~Game() {
        destroy();
    }

    // inits
    void init();
    void initConfig();
    void initLogManager(string loggerLevel);
    void initSDL();
    void initController();

    // free memory
    void destroy();


    // gameloop
    void processInput();
    void update();
    void render();

    void reboot();

    std::vector<GameObject*> gameObjects;

    void UpdateAtras(vector<Game_Component*> vector);
    void UpdateDelante(vector<Game_Component*> vector);
    void setWindowTitleWithFPS(int fps);

    std::vector <Game_Component*> obj_escenario;

    bool hasNextLevel = false;

    // wrappers
    Logger *logger; // since its a pointer allocating memory, we need to delete it later
    Config *config;
    Controller *controller;
    SDL_Window *window;
    SDL_Renderer *renderer;

    void loadHotkeys(Config* config);
    SDL_Scancode stringToScancode(std::string s);

};

#endif