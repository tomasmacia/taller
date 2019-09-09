#include "window.h"

SDL_Renderer *Window::_renderer = nullptr;

//CONSTRUCTOR & DESTRUCTOR
Window::Window(const std::string &title, int width, int height) :
_title(title), _width(width), _height(height)
{
    _closed = !init();
}

Window::~Window(){
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}

//PUBLIC
bool Window::isClosed(){return _closed;}

void Window::pollEvents(SDL_Event &event){ //HARDCODEADO
        switch (event.type)
        {
        case SDL_QUIT:
            _closed = true;
            break;
        
        default:
            break;
        }
}

void Window::display(){
    SDL_RenderPresent(_renderer); 
    SDL_SetRenderDrawColor(_renderer,0,200,0,255); //HARDCODEADO
    SDL_RenderClear(_renderer); //display del sdl2
}

//PRIVATE
bool Window::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        raiseException("failed to initialize SDL");
        return 0;
    }

    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG){
        raiseException("failed to initialize SDL_image");
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        0
    );

    if (_window == nullptr){
        raiseException("failed to create window");
        return 0;
    }

    _renderer = SDL_CreateRenderer(_window, -1,SDL_RENDERER_ACCELERATED);

    return true;
}

void Window::raiseException(std::string mesage){}

