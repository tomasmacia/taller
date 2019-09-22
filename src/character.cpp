#include <SDL2/SDL.h>
#include "character.h"

//CONSTRUCTOR && DESTRUCTOR
Character::Character(SDL_Renderer* renderer, float x, float y,
                     float minScaleFactor, float maxY, float minY,
                     bool perspectiveSensitive){
    
    Sprite* sprite = new Sprite(IMAGE_PATH,R_TRANSAPRENT,G_TRANSAPRENT,B_TRANSAPRENT);
    _entity = new Entity(renderer, MAX_WIDTH, MAX_HEIGHT, x, y, sprite,minScaleFactor, maxY, minY,
                        perspectiveSensitive); 
}

Character::~Character(){
    delete(_entity);
}

//PUBLIC
void Character::enableLeftMovement(){
    _entity->enableLeftXMotion();
}

void Character::enableRightMovement(){
    _entity->enableRightXMotion();
}

void Character::enableDeepIntoScreenMovement(){
    _entity->enableUpYMotion();
}

void Character::enableCloserToScreenMovement(){
    _entity->enableDownYMotion();
}

void Character::disableLeftMovement(){
    _entity->disableXMotion();
}

void Character::disableRightMovement(){
    _entity->disableXMotion();
}

void Character::disableDeepIntoScreenMovement(){
    _entity->disableYMotion();
}

void Character::disableCloserToScreenMovement(){
    _entity->disableYMotion();
}

void Character::jump(){

}

void Character::hit(){

}

void Character::crouch(){

}

float Character::getY(){
    return _entity->getY();
}

float Character::getWidth(){
    return _entity->getWidth();
}

float Character::getHeigth(){
    return _entity->getHeigth();
}

void Character::update(){
    _entity->update();
}

/*
void Character::updateImage(){
    

    sprite();
  //   std::cerr << state<< " * "<< state_previous<< " * "<< std::endl;
    if (spriteToload >= cant_img_sprite-1)
            {spriteToload=0;} 
    if (cont >= change )
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
            if (spriteToload >=cant_img_sprite-1){
                //si llegue al final de la secuencia, mi estado es quieto
                // y estado previo es "accion," al cargar la imagen defaullt lo hago.
                SDL_FreeSurface(_image);
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
    /*rect->x = _image->clip_rect.w/cant_img_sprite * spriteToload;
    rect->y=0;
    _texture = SDL_CreateTextureFromSurface( _render, _image );
    SDL_RenderCopyEx( _render, _texture, rect, _pos ,0,NULL,flip);

    
    SDL_DestroyTexture(_texture);
    
}
*/