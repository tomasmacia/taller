#include "window.h"
#include <iostream>

Window::Window(const std::string &title, int width, int height) :
_title(title), _width(width), _height(height)
{}

Window::~Window(){
    SDL_DestroyWindow(_window);
}

bool Window::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        raiseException(); //failed to initialize SDL.\n
        return 0;
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        0
    );

    if (_window == nullptr){
        raiseException(); //failed to create window.\n
        return 0;
    }
    return true;
}


void Window::poolEvents(){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            _closed = true;
            break;
        
        default:
            break;
        }
    }
}

void Window::raiseException(){}

bool Window::isClosed(){return _closed;}