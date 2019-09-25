#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "game.h"

using namespace std;

class Character {
public:
    Character(Game* _owner,int w, int h,SDL_Renderer* render, vector<string> pathsToSprites);
    ~Character();
    bool move(int option,int p);
    void updateImage();
    void change_limits();
    int GetPosY();
    bool inFinal();
    void setFlip(SDL_RendererFlip _flip) { flip = _flip;}
    void load_image_default(); // luego de una accion cargo sprite default   
    void mov_jump(int me_estoy_moviendo);

private:


    Game* owner;
    vector<string> path_img;
    void actions_sprites(int n, int img_);
    void moves_sprites(int n, int img_);
    void size();
    void sprite();
    void saltoParabolico();

    bool rgth = false, lft = false; //para hacer salto parabolico o no
    bool inlevel2 = true;
    SDL_RendererFlip flip =SDL_FLIP_NONE;
    int  _x,_y,_w,_h,_w_window,_h_window;
    int _v_limit; //limite vertical de movimiento

    int default_mov = 5;

    //PARA SALTO CON VELOCIDAD VARIABLE
    int default_mov_salto = 1; 
    int cant_altura_de_salto_max = -13*2*default_mov_salto; //el 13 es por la cantidad de sprites del salto de cody 
    int cant_a_desplazarse_saltando = cant_altura_de_salto_max;
    int valor_de_y_justo_antes_del_salto = 0;
    int valor_loop_previo = 0;
    int contador_saltar = 0;

    int cont=1,cont_acc = 1; //para cambio de imagen sprite
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