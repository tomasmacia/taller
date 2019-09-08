#include "window.h"
#include "events.h"


SDL_Renderer *Window::_renderer = nullptr;

//CONSTRUCTOR & DESTRUCTOR
Window::Window(const std::string &title, int width, int height) :
_title(title), _width(width), _height(height)
{
    !init();
}

Window::~Window(){
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

//PUBLIC


void Window::display(){
    SDL_RenderPresent(_renderer); 
    SDL_SetRenderDrawColor(_renderer,0,200,0,255); //HARDCODEADO
    SDL_RenderClear(_renderer); //display del sdl2
}

//PRIVATE
bool Window::init(){
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

    _renderer = SDL_CreateRenderer(_window, -1,SDL_RENDERER_ACCELERATED);

    return true;
}


void Window::raiseException(){}

