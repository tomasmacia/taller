#include <string>
#include <SDL2/SDL.h> 
#include "game/Displayable.h"
#include "game/Updateable.h"

#ifndef WINDOW_H_
#define WINDOW_H_

class Window : public Displayable, public Updateable{

public:
    static SDL_Renderer *_renderer;
    
private:
    std::string _title;
    int _width;
    int _height;

    bool _closed = false;
    
    SDL_Window *_window = nullptr;

public:
    Window(const std::string &title, int width,int height);
    ~Window();

    bool isClosed();
    void update();
    // void pollEvents(SDL_Event &event);
    void display();

private:
    bool init();
    void raiseException();
};

#endif