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
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

//PUBLIC


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


    if (_window == nullptr){
        raiseException(); //failed to create window.\n
        return 0;
    }

    return true;
};

void Window::updateWindow(){
    //Cargo las imagenes a usar y actualizo window.    
   // _imagemanager->fullLoad("Sprites/FF_Stage4_back.png","Sprites/FF_Stage4_floor.png","Sprites/cody.png",position);
    SDL_UpdateWindowSurface(_window);

};

void Window::raiseException(){}
