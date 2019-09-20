#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"

//CONSTRUCTOR & DESTRUCTOR
Window::Window(const std::string title, int width, int height) :
_title(title), _width(width), _height(height)
{
    _closed = !init();
}

Window::~Window(){
    //Destroy window
    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );
    _window = NULL;
    _renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

//PUBLIC
bool Window::isClosed(){return _closed;}

void Window::display(){
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );
    SDL_RenderClear(_renderer);
}

void Window::showAll(){
    SDL_RenderPresent(_renderer);
}

SDL_Renderer* Window::getRenderer(){
    return _renderer;
}

void Window::close(){
    _closed = true;
}

SDL_Window* Window::getWindow(){
    return _window;
}

//PRIVATE
bool Window::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        raiseException("failed to initialize SDL");
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        raiseException("failed to initialize SDL_image");
        return false;
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        SDL_WINDOW_SHOWN
    );

    if (_window == nullptr){
        raiseException("failed to create window");
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1,SDL_RENDERER_ACCELERATED);
    
    //Update the surface
    SDL_UpdateWindowSurface( _window );

    return true;
}

void Window::raiseException(std::string mesage){
    std::cout << mesage << "\n";
}

