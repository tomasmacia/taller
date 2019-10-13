#include <SDL2/SDL.h>
#include "game.h"
#include "character.h"
#include "Input.h"
#include "State.h"

#include <utility>

Character::Character(class Game* _owner, int w, int h, SDL_Renderer* render, std::vector<std::string> pathsToSprites):
    _render(render),
    owner(_owner),
    _x(w*.3 ), /*--> posicion x inicial*/ /*----> .3 y .66 son ctes que se  q sirven */
    _w(h*.3),/*--> width que debe tener*/ /*----> por lo que podria agregarse al .h */
    _h(h*.66),/*-->heigth que debe tener*/
    _y(h*.3), /*--> posicion y inicial*/
    _h_window( h), /*-->width de window*/
    _w_window( w),/*-->heigth de window*/
    path_img(std::move(pathsToSprites)) {
    _v_limit = ((_w_window)*.7)-(_w/2);  //Normalmente llega  ala mitad de la pantalla y deberia empezar a moverse el fondo.
    _pos->x = _x;//
    _pos->y = _y;//---->Parametros y posicion donde va a estar 
    _pos->h = _h;//---->la imagen de cody.
    _pos->w = _w;//----> 
    load_image_default();
    //Ancho y alto del personaje al iniciar es la misma (solo es 1 imagen por default)
    rect->w=_image->clip_rect.w;
    rect->h=_image->clip_rect.h;    
};




void Character::update(){

        //para cada input se actua distinto (Double Dispatch??)
    /*Ej:
        newInput es un botonDeGolpear que extiende de Input

        newInput->activate(this)

        >>En metodo activate de botonDeGolpear>>>

        activate(Character* character){
            character->ejecutarGolpear();
        }*/

    Input* newInput = _controller->getInput(); //si no hay input nuevo es NULL

    if (newInput){
        newInput->activate(this);
        delete newInput;
    }
}

void Character::render(){

    State* newLook = physicsComponent->getState(); //si no hay state nuevo es NULL
    graphicsComponent->update(newLook); // si es NULL usa el look anterior

    if (newLook)
        delete newLook;
}





























bool Character::move(int option,int p){
    //PARAMETRO OPTION 
    // 0 = rigth , up, down,jump,-> me indica pos del vector donde esta su spritesheet(son el mismo e
    //en los 4)
    // 2 punch, 3 = agacharse

    //PARAMETRO P
    //De las 4 acciones de movimiento me indica cual es (8 up, 4 left, 6 rigth, 2 down)
    //para realizar el movimiento.

    //Cuando salto o golpeo o  me agacho, al cargar el sprite su estado(variable de la clase)
    // pasa a accion 8  (vease como cosa que necesita un trigger y se completa sola) 
    // y en el proximo update la accion se seguira hasta completarse.
    // Si en el transurso de la accion, apreto un boton de movimiento, los ignora hasta realizar la accion.
    //Si realizo una accion espera a que se complete,para evitar interrumpcion del sprite y bugs.

    //Limites de movimiento harcodeados en relacion a imagen y pantalla

    //Como estoy realizando una accion seteo mi option a 8 para ignorar eventos.    
    if (state==8){ option=8;}
    if (state == 9){
        option=9;
        /* Solo me muevo cuando salto si antes estaba presionando left o rigth
        no si se presiona lueo de saltar*/
        if(p == 6  && rgth){
            while(_x>_v_limit ){
                _x--;           
                owner->move_all();     
            }
            _x +=default_mov*1.5;          
        }
        if(p == 4 && lft){    
            while(_x<0){_x++;}
            _x -=default_mov*1.5; //----> Limite izquierdo (X = 0)
            }
        _pos->x =_x;
        } //9 es el estado especifico del salto
    state = option;
    while(option ==0){

        if(state == 0){
            cont++;
        }
 
        if(p == 4 ){
            
            _x -=default_mov;
            while(_x<0){_x++;} //----> Limite izquierdo (X = 0)
        }
        if(p == 6 ){
            //si esoy en el limite vertical, se realiza parallax
            while(_x>_v_limit ){
                _x--;           
                owner->move_all();     
                }
                _x +=default_mov;          
        }    
        if(p == 8  ){
            /*Si camino a la derecha y subo, subo mirando a la derecha. Idem izquierda */ 
            _y -=default_mov;
            while(_y<(_h_window/5)){_y++;}//Normalmente (heigth/5) --> limite superior
        }
        if (p == 2){
            _y +=default_mov;
            while(_y>(_h_window/3)){_y--;} //(heigth/3) --> Limite inferior
            }
        _pos->x =_x;
        _pos->y= _y;  
        
        return false;
    }
    return false;     
}



void Character::mov_jump(int me_estoy_moviendo){
    if(state != 8){
        if(me_estoy_moviendo == 0){
            rgth = true;
        }
        if(me_estoy_moviendo == 1){
            lft=true;
        }
    }
}


void Character::updateImage(){

    inFinal();
    sprite();
    if (spriteToload >= cant_img_sprite-1)
            {spriteToload=0;} 
    if (cont >= change )
    //si el contador de cambio de sprites es mayor 
    //al cambio seteado
    {
        spriteToload++;//cambio de imagen sprite
        cont=0;//contador reseteado
    }
    if (state >= 8 ){    //si quiero realizar una accion
        if (state == 9){
            saltoParabolico();
        }

        cont_acc++;
        //aumento el contador de acciones
        if(cont_acc == loop){
        //si el contador es igual al numero de loops que se necesitan para
        //para pasar de imagen de sprite, vuelvo el contador a 0 y cambio de sprite en
        //la secuencia
            cont_acc = 0;
            spriteToload++;
            if (spriteToload >=cant_img_sprite-1){
                //si llegue al final de la secuencia de sprites, state y previous_state
                // es quieto, al cargar la imagen defaullt lo hago.
                SDL_FreeSurface(_image);
                rgth = lft = false;
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
    SDL_RenderCopyEx( _render, _texture, rect, _pos ,0,NULL,flip);

    
    SDL_DestroyTexture(_texture);
    
}

void Character::saltoParabolico(){
    if(contador_saltar == 0){//significa que todavia no salte nada
        valor_de_y_justo_antes_del_salto = _y;
        valor_loop_previo = loop;
        loop = 4*default_mov_salto; //salta mas lento
        contador_saltar++;
    }
    if (contador_saltar >0){
        cant_a_desplazarse_saltando = cant_a_desplazarse_saltando + default_mov_salto;
        _pos->y += cant_a_desplazarse_saltando;
        /*
        cout<<'\n';
        cout<<"i: "<<contador_saltar<<'\n';
        cout<<"srpite: "<<spriteToload<<'\n';
        cout<<"_pos->y: "<<_pos->y<<'\n';
        cout<<"cant_a_desplazarse_saltando: "<<cant_a_desplazarse_saltando<<'\n';
        cout<<"default_mov_salto: "<<default_mov_salto<<'\n';
        */
        contador_saltar++;
    }
    if (contador_saltar >0 && _pos->y >= valor_de_y_justo_antes_del_salto){//ya estoy del otro lado de la parabola
        cant_a_desplazarse_saltando = cant_altura_de_salto_max;
        _pos->y = valor_de_y_justo_antes_del_salto; //la y naturalmente deberia coincidir pero por las dudas fuerzo a restaurar el valor original
        loop = valor_loop_previo; //restaura el valor original
        contador_saltar = 0;
    }

}

void Character::sprite(){ 
    
    //Left
    moves_sprites(0,9);
    //Jump
    actions_sprites(1,13);
    //Punch
    actions_sprites(2,3);
    //Agacharse
    actions_sprites(3,4);
    //salto patada
    actions_sprites(5,13);
    // kick
    actions_sprites(6,6);
 
}

void Character::load_image_default(){
    /* Carga imagenes del sprite o muestra pantalliats azules donde
    deberia estar el pj */
    if ((_image = IMG_Load(path_img[4].c_str()))==NULL){
        LogManager::logError("No se pudo cargar el sprite del personaje.");
        LogManager::logDebug("Se carga una imagen amarilla por defecto al no encontrar el sprite del personaje.");
//        std::cerr <<  "No pudo cargar imagen.\n";
//        std::cerr << "Se carga imagen por default\n";
        _image = SDL_CreateRGBSurface(0, 56, 125, 32, 0, 0, 0, 0);
        SDL_FillRect(_image, NULL, SDL_MapRGB(_image->format, 255, 255, 0));
            }
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 88,184,248));
    state_previous= -1;
    state = -1;
    spriteToload=0;
    cant_img_sprite = 1;
    rect->w = 56;// pongo dierctamente alto y ancho
    rect->h = 125;// ya que se cuanto mide
    _pos->w =_h*56/125;
    cont = 3;

    if (contador_saltar > 0){
        cant_a_desplazarse_saltando = cant_altura_de_salto_max;
        _pos->y = valor_de_y_justo_antes_del_salto; //la y naturalmente deberia coincidir pero por las dudas fuerzo a restaurar el valor original
        loop = valor_loop_previo; //restaura el valor original
        contador_saltar = 0;
    }
}


Character::~Character(){
    SDL_DestroyTexture(_texture);
}

void Character::change_limits(){
    /* El limite de movimiento de cody ya no es la tercera parte
     de la pantalla (seteado asi) sino que es el final de la pantalla */
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
        /* Carga imagenes del sprite o muestra pantalliats azules donde
    deberia estar el pj */
    if (state == n){
        cant_img_sprite = img_;
        cont = 0;
        spriteToload = 0;
        SDL_FreeSurface(_image);
        if ((_image = IMG_Load(path_img[n].c_str()))==NULL) {
            cant_img_sprite = 2;
            LogManager::logError("No se pudo cargar el sprite del personaje.");
            LogManager::logDebug("Se carga una imagen amarilla por defecto al no encontrar el sprite del personaje.");
            _image = SDL_CreateRGBSurface(0, 112, 125, 32, 0, 0, 0, 0);
            SDL_FillRect(_image, NULL, SDL_MapRGB(_image->format, 255, 255, 0));

        }
        //transparencia la contorno celeste
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 88,184,248));

        //Cambio el estado a accion para que se complete
        if (state == 1 || state == 5) {
            state = 9;
        } else {
            state = 8;
        }

        size();
    }
}

void Character::moves_sprites(int n, int img_){
    /* cargo sprites de movimientos */
        /* Carga imagenes del sprite o muestra pantalliats azules donde
    deberia estar el pj */
    if (state == n){
        if(state_previous!=n){ 
            cant_img_sprite = img_;
            cont = 1;
            SDL_FreeSurface(_image);
            if ((_image = IMG_Load(path_img[n].c_str()))==NULL){
                cant_img_sprite = 2;
                LogManager::logError("No se pudo cargar el sprite del personaje.");
                LogManager::logDebug("Se carga una imagen amarilla por defecto al no encontrar el sprite de movimiento del personaje.");
                _image = SDL_CreateRGBSurface(0, 112, 125, 32, 0, 0, 0, 0);
                SDL_FillRect(_image, NULL, SDL_MapRGB(_image->format, 255, 255, 0));
            }
            //transparencia la contorno celeste
            SDL_SetColorKey(_image, SDL_TRUE,
            SDL_MapRGB(_image->format, 88,184,248));
            state_previous=n;
            size();
        }
    }
}


int Character::GetPosY(){
    return _y;
}


bool Character::inFinal(){
    return _x > (_w_window - _w);
}