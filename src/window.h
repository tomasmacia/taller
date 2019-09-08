#include <string>
#include "iostream"
#include <SDL2/SDL.h> 




class Window{

public:
    static SDL_Renderer *_renderer;
    
private:
    std::string _title;
    int _width;
    int _height;
    SDL_Surface* fondo = nullptr;
    SDL_Surface* personaje = nullptr;

    
    SDL_Window *_window = nullptr;

public:
    Window(const std::string &title, int width,int height);
    ~Window();
    void display();
    void loadFondo(const std::string &rute);
    void loadpj(const std::string &rute, SDL_Rect r);
private:
    bool init();
    void raiseException();
};
