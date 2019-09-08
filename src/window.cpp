#include "window.h"
#include "events.h"
#include <SDL2/SDL_image.h>
#include "iostream"


SDL_Renderer *Window::_renderer = nullptr;

//CONSTRUCTOR & DESTRUCTOR
Window::Window(const std::string &title, int width, int height) :
_title(title), _width(width), _height(height)
{
    init();
}

Window::~Window(){
    IMG_Quit();
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

    _renderer = SDL_CreateRenderer(_window, -1,SDL_RENDERER_ACCELERATED);

    return true;
}


void Window::raiseException(){}


void Window::loadpj(const std::string &image_path,SDL_Rect r)
{   if(personaje != nullptr) {
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        SDL_BlitSurface( fondo, NULL, gScreenSurface, NULL );
	    SDL_UpdateWindowSurface( _window ); 
    }
    else {

        //Obtengo surface asociada a la ventana
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        //Cargo imagen.png en una nueva Surface
        SDL_Surface* personaje = IMG_Load(image_path.c_str());
        if( personaje == NULL )
        {
            std::cerr <<  "No pudo cargar imagen.\n";
            std::cerr << "SDL Error: "<< SDL_GetError()<< ".\n";
        }
        SDL_SetColorKey(personaje, SDL_TRUE,
        SDL_MapRGB(personaje->format, 0, 0, 0));
        
        SDL_BlitSurface( personaje, NULL, gScreenSurface, &r );
        SDL_FreeSurface(personaje);
                
        //Update de surface
        SDL_UpdateWindowSurface( _window );
    }
}

void Window::loadFondo(const std::string &image_path)
{   if(fondo != nullptr) {
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        SDL_BlitSurface( fondo, NULL, gScreenSurface, NULL );
	    SDL_UpdateWindowSurface( _window ); 
    }
    else {
        //Obtengo surface asociada a la ventana
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        //Cargo imagen.png en una nueva Surface
        fondo = IMG_Load(image_path.c_str());
    	if( fondo == NULL )	{
		    std::cerr <<  "No pudo cargar imagen.\n";
            std::cerr << "SDL Error: "<< SDL_GetError()<< ".\n";
    	} 
        //Aplico imagen
        SDL_BlitSurface( fondo, NULL, gScreenSurface, NULL );
    }
    //SDL_FreeSurface(fondo);
			
	//Update de surface
	SDL_UpdateWindowSurface( _window );
}
