#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "iostream"
#include <SDL2/SDL.h>
#include "string.h"
#include <vector>
using namespace std;

class Character {
public:
    Character( int w, int h,SDL_Renderer* render);
    ~Character();
    bool move(int option,int p);
    void updateImage();
    void change_limits();
    int GetPosY();
    void setFlip(SDL_RendererFlip _flip)
    {
        flip = _flip;
    }int cont=1;
        void load_image_default(); // luego de una accion cargo sprite default   
private:
    
    vector<string> path_img;
    void _charge_vector();
    void actions_sprites(int n, int img_);
    void moves_sprites(int n, int img_);
    void size();
    void sprite();
 
    SDL_RendererFlip flip =SDL_FLIP_NONE;
    int  _x,_y,_w,_h,_w_window,_h_window;
    int _v_limit; //limite vertical de movimiento
    int default_mov = 5;   
     
    bool jump_large = false;
    const int change = 5;// constante para cambiar de imagen
    int cant_img_sprite = 1;//imagenes en una tira de sprite (default 1)
    int spriteToload = 0;//en que imagen de la tira estoy
    int loop = 5;//cantidad de loop que deben suceder para que una accion pase a la
                    //siguiente imagen del sprite
    SDL_Surface* _image; //superficie a cargar la imagen
    SDL_Texture* _texture; //textura de la imagen
    SDL_Renderer* _render = nullptr; //puntero al render
    SDL_Rect* _pos = new SDL_Rect;//rect para colocar en lugar correcto del window
    SDL_Rect* rect = new SDL_Rect; //rect para elegir imagen exacta de tira de sprite
    int state = -1 , state_previous = -1;//estado actual y previo del pj(acciones)
};
 
#endif