#include "imageManager.h"


ImageManager::ImageManager(int w, int h, SDL_Window* window):
_w(w), _h(h), _window(window){

    // Trabajar con SDL_image para cargar imagenes no .bmp   
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Fallo SDL_Image.\n";
    }
};

ImageManager::~ImageManager(){
    SDL_FreeSurface(personaje);//porque no los libero al cargarlos
    SDL_FreeSurface(fondo);
    IMG_Quit();
};

void ImageManager::fullLoad(const std::string &back_image_path,const std::string &ground_image_path,const std::string &pj_image_path,SDL_Rect pj_pos){
    loadFondo(back_image_path);
    loadFondo1(ground_image_path);
    loadpj(pj_image_path,pj_pos);
};


void ImageManager::loadpj(const std::string &image_path,SDL_Rect r)
{   if(personaje != nullptr) {
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        SDL_BlitSurface( personaje, NULL, gScreenSurface, NULL );
        SDL_FreeSurface(gScreenSurface);
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

        //Transparencia en el contorno negro de cody
        SDL_SetColorKey(personaje, SDL_TRUE,
        SDL_MapRGB(personaje->format, 0, 0, 0));
        //aplico protagonista
        SDL_BlitSurface( personaje, NULL, gScreenSurface, &r );
        SDL_FreeSurface(gScreenSurface);
        //Misma idea que con fondo cargao una vez y no libero. 
        // Ver luego con  personaje en movimiento (Sprite)
        //SDL_FreeSurface(personaje);
                
        //Update de surface
        SDL_UpdateWindowSurface( _window );
    }
}

void ImageManager::loadFondo(const std::string &image_path)
{   if(fondo != nullptr) {
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        SDL_BlitSurface( fondo, NULL, gScreenSurface, NULL );
        SDL_FreeSurface(gScreenSurface);
	//    SDL_UpdateWindowSurface( _window ); 
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
        SDL_FreeSurface(gScreenSurface);
    }
    //No aplico freesurface, para ser mas rapido como el fondo que es el mismo, lo cargo
    //una vez y lo aplico cada vez que el pj se mueva. Gasta mas memoria. 
    //SDL_FreeSurface(fondo);	
	//Update de surface
    //SDL_UpdateWindowSurface( _window );
}


void ImageManager::loadFondo1(const std::string &image_path)
{   if(fondo1 != nullptr) {
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        SDL_BlitSurface( fondo1, NULL, gScreenSurface, NULL );
        SDL_FreeSurface(gScreenSurface);
	//    SDL_UpdateWindowSurface( _window ); 
    }
    else {
        //Obtengo surface asociada a la ventana
        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(_window);
        //Cargo imagen.png en una nueva Surface
        fondo1 = IMG_Load(image_path.c_str());
    	if( fondo1 == NULL )	{
		    std::cerr <<  "No pudo cargar imagen.\n";
            std::cerr << "SDL Error: "<< SDL_GetError()<< ".\n";
    	}
        //Transparencia en el contorno negro de cody
        SDL_SetColorKey(fondo1, SDL_TRUE,
        SDL_MapRGB(fondo1->format, 0, 162, 232));
        //Aplico imagen
        SDL_BlitSurface( fondo1, NULL, gScreenSurface, NULL );
        SDL_FreeSurface(gScreenSurface);
    }
    //No aplico freesurface, para ser mas rapido como el fondo que es el mismo, lo cargo
    //una vez y lo aplico cada vez que el pj se mueva. Gasta mas memoria. 
    //SDL_FreeSurface(fondo);	
	//Update de surface
    //SDL_UpdateWindowSurface( _window );
}