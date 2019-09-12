#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL2/SDL.h>
#include "iostream" 


class Window{
    
private:
    std::string _title;
    int _width;
    int _height;


public:
    Window(const std::string &title, int width,int height);
    ~Window();    void updateWindow();    
    SDL_Window *_window = nullptr;
    SDL_Renderer* renderer = nullptr;

private:
    bool init();
    void raiseException();
    
};

#endif
