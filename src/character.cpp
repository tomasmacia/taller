#include "character.h"
#include <SDL2/SDL_image.h>

Character::Character(const std::string &image_path,  int w, int h, SDL_Renderer* render):
    _render(render),
    _x(w*.3 ), /*--> posicion x inicial*/ /*----> .3 y .66 son ctes que se  q sirven */
    _w(h*.3),/*--> width que debe tener*/ /*----> por lo que podria agregarse al .h */
    _h(h*.66),/*-->heigth que debe tener*/
    _y(h*.3), /*--> posicion y inicial*/
    _h_window( h), /*-->width de window*/
    _w_window( w)/*-->heigth de window*/{
    _v_limit = (_w_window/2)-(_w/2);  //Normalmente llega  ala mitad de la pantalla
                                     //y deberia empezar a moverse el fondo.
    _pos->x = _x;//
    _pos->y = _y;//---->Parametros y posicion donde va a estar 
    _pos->h = _h;//---->la imagen de cody.
    _pos->w = _w;//-----> 

    _image = IMG_Load(image_path.c_str());
    if( _image == NULL )	{
	    std::cerr <<  "No pudo cargar imagen.\n";
        std::cerr << "SDL Error: "<< SDL_GetError()<< ".\n";
    	}
    //Transparencia al contorno celeste de cody
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 88,184,248));
    //Ancho y alto del personaje al iniciar es la misma (solo es 1 imagen por default)
    rect->w=_image->clip_rect.w;
    rect->h=_image->clip_rect.h;
    _charge_vector();
};

bool Character::move(int option){ 
    //0 =left ; 1 = rigth , 5 = up, 6 = down, 2 = jump, 3 = punch, 4 = agacharse
    // 8 = accion (vease como cosa que necesita un trigger y se completa sola) 
    // -1 = quieto ; 
    //Si realizo una accion espera a que se complete (creeria que es para evitar saltos dobles)
    
    //Limites de movimiento harcodeados en relacion a imagen y pantalla
  //  std::cerr << state << " - " << state_previous<<" - "<<option<< std::endl;
    while (state !=8)
    {         
        cont++;
        if (spriteToload==cant_img_sprite-1)
            {spriteToload=0;} 
        if(option == 0 ){
            _x -=default_mov;
            while(_x<0){_x++;} //----> Limite izquierdo (X = 0)
        }
        if(option == 1 ){
             while(_x>_v_limit ){
                _x--;           
                return true;     
                } 
            _x +=default_mov;          
        }    
        if(option == 5  ){
            /*Si camino a la derecha y subo, subo mirando a la derecha. Idem izquierda */
            if (state_previous ==-1 or 1) 
                {option = 1;}             
            if (state_previous == 0)      
                {option = 0;}
            _y -=default_mov;
            while(_y<(_h_window/5)){_y++;}//Normalmente (heigth/5) --> limite superior
        }   
        if(option == 6){
            /*Si camino a la izquierda y bajo, bajo mirando a la derecha. Idem izquierda*/      
            if (state_previous ==-1 or 1)
                {option = 1;}
            if (state_previous == 0)
                {option = 0;}
            _y +=default_mov;
            while(_y>(_h_window/3)){_y--;} //(heigth/3) --> Limite inferior
        }
        //actualizo estados
        state_previous=state;
        state = option;
        _pos->x= _x;
        _pos->y= _y;
        //¿verifico sprites cuando actualizo imagen(todas la veces en el loop)
        // o cuando se mueve cody ?
       // sprite();
        return false;
    }

    /* Estos if son para poder moverse si se realizo un salto. Por ahora
       el salto es solo mirando a la derecha (se mueve en ambos sentidos). */
    if (state_previous == 1  ) {
        while(_x>_v_limit ){
            _x--;
            return true;
        } 
        _x +=default_mov;         
    }
    if (state_previous == 0  ) {
            _x -=default_mov;
            while(_x<0){_x++;}         
    }  
    _pos->x= _x;
    return false;
};

void Character::updateImage(){
    sprite();
    if (cont >= change and state == state_previous)
    //si el contador de cambio de sprites es mayor 
    //al cambio seteado y si estoy apretando el
    //mismo boton
    {
        spriteToload++;//cambio de imagen sprite
        cont=0;//contador reseteado
    }
    if (state >= 8 ){
    //si quiero realizar una accion
        cont++;
        //aumento el contador de acciones
        if(cont == loop){
        //si el contador es igual al numero que creo es
        //vuelvo el contador a 0 y cambio de sprite en
        //la secuencia
            cont = 0;
            spriteToload++;
            if (spriteToload ==cant_img_sprite-1){
                //si llegue al final de la secuencia, mi estado es quieto
                // y estado previo es "accion," al cargar la imagen defaullt lo hago.
                load_image_default();

            }
        }
    }/* Lo de la tira de imagenes es asi, yo se la cantidad que hay(cant_img_sprite)
    y se cuanto mide de ancho la imagen(_image->clip_rect.w). Con Rect elijo 
    que parte de la imagen agarro, lo alto (linea 191) es la mismo para todas los recortes,
     al igual que la posicion y(=0) y lo ancho (linea 190).
    Pero la posicion x cambia. Contando en que imagen del total me encuentro (spriteToload)
    cada vez que aprieto una tecla que realize algo, calcula donde debe cortar, corta y
    hace un resize(el render) y lo coloca donde debe estar.

    Dato: Las imagenes deben tener una separacion uniforme para realizar un corte "lindo"
    
    x=0        x=wide/cant  x=2*wide/cant   .........etc
            
    .........................................................................    
    .           .           .           .           .           .           .
    .           .           .           .           .           .           .
    .           .           .           .           .           .           .
    .           .           .           .           .           .           .
    .           .           .           .           .           .           .
    .           .           .           .           .           .           .
    .           .           .           .           .           .           .
    .........................................................................
    */
    rect->x = _image->clip_rect.w/cant_img_sprite * spriteToload;
    rect->y=0;
    _texture = SDL_CreateTextureFromSurface( _render, _image );
    SDL_RenderCopy( _render, _texture, rect, _pos );
    SDL_DestroyTexture(_texture);
    
}

void Character::sprite(){ 
    //Left
    moves_sprites(0,9);
    //Rigth
    moves_sprites(1,9);
    //Jump
    actions_sprites(2,13);
    //Punch
    actions_sprites(3,3);
    //Agacharse
    actions_sprites(4,4);
 
}

Character::~Character(){
    SDL_DestroyTexture(_texture);
    path_img.clear();
}

void Character::load_image_default(){
    SDL_FreeSurface(_image);
    _image = IMG_Load("Sprites/cody.png");
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 88,184,248));
    state_previous= state;
    state = -1;
    spriteToload=0;
    cant_img_sprite = 1;
    rect->w = 56;// pongo dierctamente alto y ancho
    rect->h = 125;// ya que se cuanto mide
    _pos->w =_h*56/125;
    cont = 3;
    
}

void Character::change_limits(){
    /* El limite de movimiento de cody ya no es la mitad de pantalla
    sino que es el final de la pantalla */
    _v_limit = (_w_window)- _w;
}

void Character::size(){
    /* Recalculo width, heigth de rect(donde lo saco) y width de pos(donde debe ir) 
    al cargar nueva tira de sprites */
    rect->w=_image->clip_rect.w/cant_img_sprite;
    rect->h=_image->clip_rect.h;
    /* La tira de imagenes punch tiene un ancho promedio de 74, las demas
    (tanto caminar, saltar) tienen un ancho de 56. Por lo que tengo que
    recalcular el ancho o sino al dar golpes el personaje se "aplana" */
    _pos->w =_h*(rect->w)/_image->clip_rect.h;   
}

void Character::actions_sprites(int n,int img_){
    /* Cargo sprites de acciones */
    if (state == n){
            cant_img_sprite = img_;
            cont = 0;
            spriteToload = 0;
            SDL_FreeSurface(_image);
            _image = IMG_Load(path_img[n].c_str());
            //transparencia la contorno celeste
            SDL_SetColorKey(_image, SDL_TRUE,
            SDL_MapRGB(_image->format, 88,184,248));
            //Cambio el estado a accion para que se complete
            state=8;
            size();      
    }
}
void Character::moves_sprites(int n, int img_){
    /* cargo sprites de movimientos */
    if (state == n){ 
        if(state_previous!=n){ 
            cant_img_sprite = img_;
            cont = 1;
            SDL_FreeSurface(_image);
            _image = IMG_Load(path_img[n].c_str());
            //transparencia la contorno celeste
            SDL_SetColorKey(_image, SDL_TRUE,
            SDL_MapRGB(_image->format, 88,184,248));
            state_previous=n;
            size();
        }
    }
}

void Character::_charge_vector(){
    /* Cargo vector de sprites del personaje*/
    /* Las posiciones de las imagenes son las mismas que el codigo de 
    sus acciones/movimientos. */
    path_img.push_back("Sprites/codyLeft.png");
    path_img.push_back("Sprites/codyRgth.png");
    path_img.push_back("Sprites/cody_jump.png");
    path_img.push_back("Sprites/cody_punch.png");
    path_img.push_back("Sprites/cody_agacharse.png");

}