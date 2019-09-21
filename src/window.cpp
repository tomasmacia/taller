#include "window.h"
#include "iostream"
#include <SDL2/SDL_image.h>



//CONSTRUCTOR & DESTRUCTOR
Window::Window(const std::string &title, int width, int height) :
_title(title), _width(width), _height(height)
{
    init();
}

Window::~Window(){
    IMG_Quit();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(_window);
}


//PRIVATE
bool Window::init(){
    // Trabajar con SDL_image para cargar imagenes no .bmp   
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Fallo SDL_Image.\n";
    }

   // std::cerr << "SDL_Image.\n";
    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        0
    );

    render = SDL_CreateRenderer( _window, -1, SDL_RENDERER_PRESENTVSYNC);
    return true;
}

void Window::updateWindow(){
    //Actualizo window. 
    SDL_RenderPresent( render );
};

void Window::raiseException(){}
