#include "character.h"
#include <SDL2/SDL_image.h>

Character::Character(const std::string &image_path,  int w, int h):
    _x(w*0.4), /*--> posicion x inicial*/
    _w(h*.3),/*--> width que debe tener*/
    _h(h/2),/*-->heigth que debe tener*/
    _y(h/2.475), /*--> posicion y inicial*/
    _h_window( h), /*-->width de window*/
    _w_window( w)/*-->heigth de window*/{
    _pos->x = _x;//
    _pos->y = _y;//---->Parametros con los que hago un resize a 
    _pos->h = _h;//---->la imagen. EN el BlitScale le paso un Rect
    _pos->w = _w;//----->que tenga el tamaño que deseo
    _image = IMG_Load(image_path.c_str());
    if( _image == NULL )	{
	    std::cerr <<  "No pudo cargar imagen.\n";
        std::cerr << "SDL Error: "<< SDL_GetError()<< ".\n";
    	}
        //Transparencia al contorno negro de cody
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0,0,0));
};

bool Character::move(int option){ 
    //0 =left ; 1 = rigth , 2 = up, 3 = down
    // 4 = accion(vease como cosa que necesita un trigger y se completa sola) 
    // -1 = quieto
    while (state != 4){
        int default_mov = 6;           
        cont++;
        if (spriteToload==cant_img_sprite-1)
            {spriteToload=0;}
        if(option == 0 ){
                state=0;
        //       sprite();
                //Limites de movimiento harcodeados en relacion a imagen y pantalla
                _x -=default_mov;
                while(_x<0){_x++;} 
            }
        if(option == 1 ){
            state = 1;
            sprite();
            while(_x>(_w_window/2)-(_w/2)){
                _x--;
                _pos->x= _x;//(width ventana/2) - (width de la imagen/2) Normalmente llega  ala mitad de la imagen y
                _pos->y= _y;// deberia empezar a moverse el fondo-->Para Futuro
                return true;
                } 
            _x +=default_mov;          
        }    
        if(option == 2 ){
            state = 1;
            sprite();        
            _y -=default_mov;
            while(_y<(_h_window/3)){_y++;}//Normalmente (heigth/3)
        }   
        if(option == 3){
            state = 1;
            sprite();
            _y +=default_mov;
            while(_y>(_h_window/2)){_y--;} //(heigth/2)
        }
        if (option == 4){
            state = -1;
        }
        _pos->x= _x;
        _pos->y= _y;
        return false;
        }
    return false;
};

void Character::updateImage(SDL_Window* window){
    if (cont >= change & state == state_previous)
    //si el contador de cambio de sprites es mayor 
    //al cambio seteado o si estoy apretando el
    //mismo boton
    {
        spriteToload++;//cambio de imagen sprite
        cont=0;//contador reseteado
    }
    if (state == 4){
    //si quiero realizar una accion
        cont++;
        //aumento el contador de acciones
        if(cont == 50){
        //si el contador es igual al numero que creo q es
        //vuelvo el contador a 0 y cambio de sprite en
        //la secuencia
            cont = 0;
            spriteToload++;
            if (spriteToload ==cant_img_sprite-1){
                //si llegue al final de la secuencia, mi estado es "quieto"
                state = -1;
            }
        }
    }
    rect->x = _image->clip_rect.w/cant_img_sprite * spriteToload;
    rect->y=0;
    rect->w=_image->clip_rect.w/cant_img_sprite;
    rect->h=_image->clip_rect.h;
    SDL_Surface* gScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,rect, gScreenSurface,_pos);
    SDL_FreeSurface(gScreenSurface);
    };

void Character::sprite(){
    if (state ==1){ ///si quiero caminar
        if(state_previous!=1){ //si no estaba caminando, cargo los sprites
            std::cerr << "right\n";//si ya estaba caminando no los cargo
            cant_img_sprite = 6;
            cont = 0;
            _image = IMG_Load("Sprites/codyall.png");
            //transparencia la contorno celeste
            SDL_SetColorKey(_image, SDL_TRUE,
            SDL_MapRGB(_image->format, 88,184,248));
            state_previous=1;
        }

        
    }
 //       std::cerr << "1 paso"<< std::endl;
/*    }
    else if (cont==4){
        _image = IMG_Load("Sprites/cody2.png");
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0,0,0));
   //     std::cerr << "2 paso"<< std::endl;
    }
    else if (cont==8){
        _image = IMG_Load("Sprites/cody3.png");
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0,0,0));
    //    std::cerr << "3 paso"<< std::endl;
    }
    else if (cont==12){
        _image = IMG_Load("Sprites/cody4.png");
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0,0,0));
    //    std::cerr << "4 paso"<< std::endl;
    }
    else if (cont==16){
        _image = IMG_Load("Sprites/cody5.png");
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0,0,0));
     //   std::cerr << "5 paso"<< std::endl;
    }
    else if (cont==20){
        _image = IMG_Load("Sprites/cody6.png");
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0,0,0));
    //    std::cerr << "6 paso"<< std::endl;
        cont=-4;
    }*/
}


