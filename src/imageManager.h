#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "iostream"

class ImageManager{

public:

    ImageManager(int w,int h, SDL_Window* window);
    //Pido width y heigth para usarlo. Si a futuro encuentro forma de hacer
    //un resize del fondo y el pj en relacion al tamaño de la ventana(que ocupe toda la pantalla las imagenes)
    void fullLoad(const std::string &back_image_path,const std::string &ground_image_path,const std::string &pj_image_path,SDL_Rect pj_pos);
    ~ImageManager();

private:
    SDL_Window* _window = nullptr;
    //Surface para fondos y pj , idea temporal.
    SDL_Surface* fondo = nullptr;
    SDL_Surface* fondo1 = nullptr;
    SDL_Surface* personaje = nullptr;
    int _w;
    int _h;
    int cont = 0;
    int cont2 = 0;
   //Estos 3 metodos hacen basicamente lo mismo, buscar forma
    //de hacerlo en un metodo.
    void loadpj(const std::string &image_path,SDL_Rect r);

    void loadFondo(const std::string &image_path);

    void loadFondo1(const std::string &image_path);

};